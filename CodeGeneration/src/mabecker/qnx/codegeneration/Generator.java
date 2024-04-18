package mabecker.qnx.codegeneration;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.ArrayList;
import java.util.Map;

import mabecker.qnx.codegeneration.model.Core;
import mabecker.qnx.codegeneration.model.EdgeSystem;
import mabecker.qnx.codegeneration.model.QnxLabel;
import mabecker.qnx.codegeneration.model.QnxNode;
import mabecker.qnx.codegeneration.model.QnxTask;

public class Generator {

	private static String 		inputFilename;	// Path to the original Amalthea model
	private static String 		basePath;		// Base path for the generated files
	private static EdgeSystem 	system;			// Edge System instance 
	
	/**
	 * Top-level method for the code generation. Generates QNX projects for each 
	 * node of the system. 
	 * @param system	EdgeSystem model to generate code from.
	 * @param _outputPath Destination for the QNX projects.
	 * @param _compile Flag to indicate if the project should be compiled automatically.
	 * @param _trnasfer Flag to indicate if the executables should be transfered to the hardware nodes automativally.
	 */
	public static void generateCode(EdgeSystem _system, String _outputPath, boolean _compile, boolean _transfer) {
		inputFilename = _system.getModelPath();
		basePath = _outputPath;
		system = _system;
		
		// Create the set of nodes that has tasks assigned to its
		ArrayList<QnxNode> activeNodes = new ArrayList<QnxNode>();
		for (QnxNode n : system.getNodes()) {
			if (n.getAllTasks().size() > 0) {
				activeNodes.add(n);
			}
		}
		
		long start = System.nanoTime();
		
		prepareProject(activeNodes);	// Prepare folder structure and copy base project
		
		long copied = System.nanoTime();
		
		System.out.println("\n=======================================================================");
		System.out.println("= Generate Code");
		System.out.println("=======================================================================");
		
		// Generate label configuration
		generateLabelsHeader(activeNodes);
		generateLabelsSource(activeNodes);
		
		// Generate the runnable code
		generateRunnableHeader(activeNodes);
		generateRunnableSrc(activeNodes);
		
		// Generate system configuration
		generateSysConfHeader(activeNodes);
				
		// Generate channel configuration
		generateChannelConfHeader(activeNodes);
		
		// Generate the shell script to transfer the executable 
		generateShellScripts(activeNodes);
		
		long generated = System.nanoTime();
		
		// Compile the project for each node
		if (_compile) compile(activeNodes);
		
		long compiled = System.nanoTime();
		
		// Transfer the executable to each node
		if (_transfer) transfer(activeNodes);
		
		System.out.println("Copy Base Project: " + (copied - start) / 1000000 + " ms");
		System.out.println("Generate Files: " + (generated - copied) / 1000000 + " ms");
		System.out.println("Compiled: " + (compiled - copied) / 1000000 + " ms");
	}
	
	/**
	 * Create the directory if it does not exist yet
	 * @param _dirName
	 */
	private static String makeDirectory(String _dirName) {
		File directory = new File(_dirName);
		
		System.out.println("Make directory: " + _dirName);
	    if (! directory.exists()){
	        directory.mkdirs();
	        // If you require it to make the entire directory path including parents,
	        // use directory.mkdirs(); here instead.
	    }
	    
	    String path = "";
		try {
			path = directory.getCanonicalPath();
		} catch (IOException e) {
			e.printStackTrace();
		}
	    
	    return path;
	}
	
	/**
	 * Remove the given directory and all its content.
	 * This is used to clean the target project folder if forceReload is true.
	 * @param directoryToBeDeleted
	 * @return
	 */
	private static boolean deleteDirectory(File directoryToBeDeleted) {
		
	    File[] allContents = directoryToBeDeleted.listFiles();
	    if (allContents != null) {
	        for (File file : allContents) {
	            deleteDirectory(file);
	        }
	    }
	    return directoryToBeDeleted.delete();
	}
	
	/**
	 * This method prepares the project structure and copies the base project for each node
	 */
	public static void prepareProject(ArrayList<QnxNode> nodes) {
		
		System.out.println("\n=======================================================================");
		System.out.println("= Prepare folder structure ");
		System.out.println("=======================================================================");
		
		File dir = new File(basePath);
		if ( dir.exists()){
			deleteDirectory(dir);
		}
		
		// Prepare the directory for the code generation
		makeDirectory(basePath);
		
		// Create a copy of the input AMALTHEA files in the folder for code generation
		copyAmaltheaFiles(inputFilename, basePath);
		
		// Copy the base project for each of the ECUs
		for(QnxNode node : nodes) {
			copyBaseProject(basePath + '/' + node.getName());
		}
	}
	
	/**
	 * Method copies all Amalthea model files to the generated project. 
	 * The files are not used directly but copied to keep consisteny between the generated QNX project and the
	 * model files at its base.
	 * @param _foldername Folder with the Amalthea files.
	 * @param _destination Destination folder.
	 */
	public static void copyAmaltheaFiles(String _foldername, String _destination) {
		Path sourceDir = Paths.get(_foldername);
		Path destinationDir = Paths.get(_destination);
		
		System.out.println("\n=======================================================================");
		System.out.println("= Copy Amalthea model files " + _destination);
		System.out.println("=======================================================================");
		
		// Traverse the file tree and copy each file/directory.
		try {
			Files.walk(sourceDir)
			.forEach(sourcePath -> {
				if (sourcePath.toString().contains(".amxmi")) {
					try {
						if (!sourcePath.toString().contains(".DS_Store") && !sourcePath.toString().contains("build") && !sourcePath.toString().contains(".kev")) {
							Path targetPath = destinationDir.resolve(sourceDir.relativize(sourcePath));
							System.out.printf("Copying %s to %s%n", sourcePath, targetPath);
							Files.copy(sourcePath, targetPath, StandardCopyOption.COPY_ATTRIBUTES);
						}
					} catch (IOException ex) {
						System.out.format("I/O error: %s%n", ex);
					}
				}
			});
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * This method creates a copy of the base project which is used for each ECU.
	 * @param destination
	 */
	public static void copyBaseProject(String destination) {
		Path sourceDir = Paths.get("../QNX_EdgeSys_Base");
		Path destinationDir = Paths.get(destination);

		System.out.println("\n=======================================================================");
		System.out.println("= Copy the base project to " + destination);
		System.out.println("=======================================================================");
		
		// Traverse the file tree and copy each file/directory.
		try {
			Files.walk(sourceDir)
			.forEach(sourcePath -> {
				try {
					if (!sourcePath.toString().contains(".DS_Store") && !sourcePath.toString().contains("build") && !sourcePath.toString().contains(".kev")) {
						Path targetPath = destinationDir.resolve(sourceDir.relativize(sourcePath));
						System.out.printf("Copying %s to %s%n", sourcePath, targetPath);
						Files.copy(sourcePath, targetPath, StandardCopyOption.COPY_ATTRIBUTES);
					}
				} catch (IOException ex) {
					System.out.format("I/O error: %s%n", ex);
				}
			});
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
	
	/**
	 * Generate the header file labels_conf.h for each node.
	 */
	private static void generateLabelsHeader(ArrayList<QnxNode> nodes) {
		FileWriter headerFile;
	
		for (QnxNode node : nodes) {
			String path = basePath + '/' + node.getName() + "/src/labels_conf.h";
			System.out.println("Generating: " + path);
			
			try {		
				headerFile = new FileWriter(path);
				headerFile.write(LabelsGen.generateHeader(system.getLabels()).toString());
				headerFile.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * Generate the source file labels_conf.c for each node.
	 */
	private static void generateLabelsSource(ArrayList<QnxNode> nodes) {
		FileWriter headerFile;
	
		for (QnxNode node : nodes) {
			String path = basePath + '/' + node.getName() + "/src/labels_conf.c";
			System.out.println("Generating: " + path);
			
			try {		
				headerFile = new FileWriter(path);
				headerFile.write(LabelsGen.generateSource(system.getLabels()).toString());
				headerFile.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * Generate the shell script to upload the executable to the target node and change file permission to 
	 * be able to execute it on the node.
	 */
	private static void generateShellScripts(ArrayList<QnxNode> nodes) {
		FileWriter shellWriter;
		
		for (QnxNode node : nodes) {
			String path = basePath + '/' + node.getName() + "/transfer.sh";
			System.out.println("Generating: " + path);
			
			try {		
				shellWriter = new FileWriter(path);
				shellWriter.write(ScripGen.generateUploadScript(node.getIpAddress(), system.getName()).toString());
				shellWriter.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			Path filePath = Paths.get(path);
			try {
				Files.setPosixFilePermissions(filePath, PosixFilePermissions.fromString("rwxr-xr-x"));
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * Generate the header file user_runnables.h for each node.
	 */
	private static void generateRunnableHeader(ArrayList<QnxNode> nodes) {
		FileWriter headerFile;
	
		for (QnxNode node : nodes) {
			String path = basePath + '/' + node.getName() + "/src/user_runnables.h";
			System.out.println("Generating: " + path);
			
			try {		
				headerFile = new FileWriter(path);
				headerFile.write(RunnableGen.generateHeader(node.getAllRunnables()).toString());
				headerFile.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * Generate the source file user_runnables.c for each node.
	 */
	private static void generateRunnableSrc(ArrayList<QnxNode> nodes) {
		FileWriter srcFile;
	
		for (QnxNode node : nodes) {
			String path = basePath + '/' + node.getName() + "/src/user_runnables.c";
			System.out.println("Generating: " + path);
			
			try {		
				srcFile = new FileWriter(path);
				srcFile.write(RunnableGen.generateSrc(node.getAllRunnables(), node).toString());
				srcFile.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * Generate the header file sysConfig.h for each node.
	 */
	private static void generateSysConfHeader(ArrayList<QnxNode> nodes) {
		FileWriter headerFile;
		
		for (QnxNode node : nodes) {
			String path = basePath + '/' + node.getName() + "/src/sysConfig.h";
			System.out.println("Generating: " + path);
			
			try {		
				headerFile = new FileWriter(path);
				headerFile.write(SysConfGen.generateHeader(node.getName(), 30000, false, false, node).toString());
				headerFile.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * Generate the header file sysConfig.h for each node.
	 */
	private static void generateChannelConfHeader(ArrayList<QnxNode> nodes) {
		FileWriter headerFile;
		
		for (QnxNode node : nodes) {
			String path = basePath + '/' + node.getName() + "/src/channel_conf.h";
			System.out.println("Generating: " + path);
			
			try {		
				headerFile = new FileWriter(path);
				headerFile.write(ChannelConfGen.generateHeader(node.getAllChannels()).toString());
				headerFile.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * Return the string of all labels used to initialise the array of label ID's.
	 * Used during code generation.
	 * @param labels List of labels.
	 * @return String to describe all labels.
	 */
	public static String generateLabelString(ArrayList<QnxLabel> _labels) {
		String s = "";
		
		for (int i = 0; i < _labels.size(); i++) {
			QnxLabel l = _labels.get(i);
			
			s += "L_" + l.getName().toUpperCase();
			
			if (i < _labels.size() - 1) {
				s += ", ";
			}
		}
		
		return s;
	}
	
	/**
	 * Returns the core affinity string for the task.
	 * @param _task QNX task.
	 * @return core affinity string
	 */
	public static String generateCoreAffinityString(QnxTask _task) {
		String s = "";
		
		for (int i = 0; i < _task.getCoreAffinity().size(); i++) {
			Core c = _task.getCoreAffinity().get(i);
			s += "CORE" + c.getId();
			if (i < _task.getCoreAffinity().size() - 1) {
				s += "|";
			}
		}
		
		return s;
	}
	
	/**
	 * Generate the bitmask that represents the core in the affinity mask.
	 * The core indicates the bit position that must be set. 
	 * @param _core Core to get the bitmask for.
	 * @return integer that represents the bit pattern if seen in binary form.
	 */
	public static int generateCoreBitmap(Core _core) {
		double power = Math.pow(2, _core.getId());
		
		return (int) power;
	}
	
	/**
	 * This method calls the compile script for each ECU 
	 */
	private static void compile(ArrayList<QnxNode> nodes) {
		for(QnxNode node : nodes) {
			
			System.out.println("\n=======================================================================");
			System.out.println("= Compiling Node: " + node.getName());
			System.out.println("=======================================================================");
			File file = new File(basePath + '/' + node.getName());
			String absolute;
			try {
				absolute = file.getCanonicalPath();
				System.out.println(absolute);
				
				
				ProcessBuilder pb = new ProcessBuilder().command("/bin/Zsh", "./compile.sh");
				
				/**
				 * Not sure why those need to be set here, they are also set in compile.sh but 
				 * error messages then indicate that they are missing?!
				 */
				Map<String, String> env = pb.environment();
				env.put("QNX_HOST", "/Users/mabecker/qnx710/host/darwin/x86_64");
				env.put("QNX_TARGET", "/Users/mabecker/qnx710/target/qnx7");
				
				Process p = pb.directory(new File(absolute))
						.redirectErrorStream(true)
						.start();
				
				BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));

				String line = "";
				while ( (line = reader.readLine()) != null) {
					System.out.println(line);
				}
				
				
				int exitValue = p.waitFor();
				System.out.println("Exit value: " + exitValue);
				
				if (exitValue != 0) System.exit(1);
				
			} catch (IOException e1) {
				e1.printStackTrace();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * Method transfers the compiled binaries to the QNX targets
	 */
	private static void transfer(ArrayList<QnxNode> nodes) {
		for(QnxNode node : nodes) {
			System.out.println("\n=======================================================================");
			System.out.println("= Tarnsfer to Node: " + node.getName());
			System.out.println("=======================================================================");
			
			File file = new File(basePath + '/' + node.getName());
			String absolute;
			
			try {
				absolute = file.getCanonicalPath();
				System.out.println(absolute);
				
				ProcessBuilder pb = new ProcessBuilder().command("./transfer.sh");
				
				/**
				 * Not sure why those need to be set here, they are also set in compile.sh but 
				 * error messages then indicate that they are missing?!
				 */
				Map<String, String> env = pb.environment();
				env.put("PATH", env.get("PATH") + ":/usr/local/bin");
				
				Process p = pb.directory(new File(absolute))
						.redirectErrorStream(true)
						.start();
				
				BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));

				String line = "";
				while ( (line = reader.readLine()) != null) {
					System.out.println(line);
				}
				
				
				int exitValue = p.waitFor();
				System.out.println("Exit value: " + exitValue);
				
				if (exitValue != 0) System.exit(1);
				
			} catch (IOException e1) {
				e1.printStackTrace();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
