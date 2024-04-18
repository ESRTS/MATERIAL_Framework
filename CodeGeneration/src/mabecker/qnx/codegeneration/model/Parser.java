package mabecker.qnx.codegeneration.model;

import java.io.File;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Map.Entry;

import org.eclipse.app4mc.amalthea.model.ASILType;
import org.eclipse.app4mc.amalthea.model.ActivityGraphItem;
import org.eclipse.app4mc.amalthea.model.Amalthea;
import org.eclipse.app4mc.amalthea.model.AmaltheaFactory;
import org.eclipse.app4mc.amalthea.model.ConstraintsModel;
import org.eclipse.app4mc.amalthea.model.FrequencyUnit;
import org.eclipse.app4mc.amalthea.model.Group;
import org.eclipse.app4mc.amalthea.model.HWModel;
import org.eclipse.app4mc.amalthea.model.HwModule;
import org.eclipse.app4mc.amalthea.model.HwPort;
import org.eclipse.app4mc.amalthea.model.HwStructure;
import org.eclipse.app4mc.amalthea.model.IntegerObject;
import org.eclipse.app4mc.amalthea.model.Label;
import org.eclipse.app4mc.amalthea.model.LabelAccess;
import org.eclipse.app4mc.amalthea.model.LabelAccessEnum;
import org.eclipse.app4mc.amalthea.model.LimitType;
import org.eclipse.app4mc.amalthea.model.OSModel;
import org.eclipse.app4mc.amalthea.model.OperatingSystem;
import org.eclipse.app4mc.amalthea.model.PeriodicStimulus;
import org.eclipse.app4mc.amalthea.model.ProcessRequirement;
import org.eclipse.app4mc.amalthea.model.ProcessingUnit;
import org.eclipse.app4mc.amalthea.model.Requirement;
import org.eclipse.app4mc.amalthea.model.io.AmaltheaLoader;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.app4mc.amalthea.model.Runnable;
import org.eclipse.app4mc.amalthea.model.RunnableCall;
import org.eclipse.app4mc.amalthea.model.SchedulerAllocation;
import org.eclipse.app4mc.amalthea.model.SchedulingParameterDefinition;
import org.eclipse.app4mc.amalthea.model.Severity;
import org.eclipse.app4mc.amalthea.model.Stimulus;
import org.eclipse.app4mc.amalthea.model.StructureType;
import org.eclipse.app4mc.amalthea.model.Switch;
import org.eclipse.app4mc.amalthea.model.SwitchEntry;
import org.eclipse.app4mc.amalthea.model.Task;
import org.eclipse.app4mc.amalthea.model.TaskAllocation;
import org.eclipse.app4mc.amalthea.model.TaskScheduler;
import org.eclipse.app4mc.amalthea.model.Ticks;
import org.eclipse.app4mc.amalthea.model.TimeMetric;
import org.eclipse.app4mc.amalthea.model.TimeRequirementLimit;
import org.eclipse.app4mc.amalthea.model.TimeUnit;
import org.eclipse.app4mc.amalthea.model.Value;
import org.eclipse.app4mc.amalthea.model.impl.PeriodicStimulusImpl;
import org.eclipse.app4mc.amalthea.model.impl.StringObjectImpl;

public class Parser {

	private static Amalthea 	model;		// Amalthea model
	private static EdgeSystem	system;		// Edge System 
	
	/**
	 * This method parses the Amalthea model and generates an instance of EdgeSystem. 
	 * The EdgeSystem additionally describes the communication threads needed to realize the application.
	 * @param _appName Name of the application.
	 * @param _foldername Name of the folder with all Amalthea file.
	 * @return EdgeSystem instance representing the Amalthea model.
	 */
	public static EdgeSystem parse(String _appName, String _foldername) {
		
		long start = System.nanoTime();
		
		//File inputFile = new File(_filename);
		
		//model = AmaltheaLoader.loadFromFile(inputFile);
		
		model = loadModel(_foldername);
		
		system = new EdgeSystem(_appName, _foldername);
		
		System.out.println("\n=======================================================================");
		System.out.println("= Parsing System");
		System.out.println("=======================================================================");
		
		/**
		 * Parse the different model elements. The parsing sequence is important as
		 * later parts might depend on earlier parsed elements.
		 */
		parseLabels();
		parseRunnables();
		parseTasks();
		parseConstraints();
		parseHardware();
		parseOs();
		parseTaskAllocation();
		
		long afterParsing = System.nanoTime();
		
		generateCommunicationChannels();
		//printAllLabels();
		//printAllRunnables();
		//printAllTasks();
		//printPlatform();
		printPlatform();
		
		long finish = System.nanoTime();
		
		System.out.println("Parsing: " + (afterParsing - start) / 1000000 + " ms");
		System.out.println("Adding Model Elements: " + (finish - afterParsing) / 1000 + " us");
		return system;
	}
	
	/**
	 * Method parses all labels from the model and adds them to the system.
	 */
	private static void parseLabels() {
		
		for (Label l : model.getSwModel().getLabels()) {
			String name = l.getName();
			long size = l.getSize().getNumberBytes();
			
			QnxLabel tmp = new QnxLabel(name, size);
			system.addLabel(tmp);
		}
	}
	
	/**
	 * Method parses all runnables from the model and adds them to the system.
	 */
	private static void parseRunnables() {
		
		for (Runnable r : model.getSwModel().getRunnables()) {
			String name = r.getName();
			int criticality = asilToInt(r.getAsilLevel());
			
			QnxRunnable tmpRunnable = new QnxRunnable(name, QnxRunnableType.USER_RUNNABLE);
			
			tmpRunnable.setCriticality(criticality);
			
			for (ActivityGraphItem item : r.getActivityGraph().getItems()) {
				
				if (item instanceof LabelAccess) {
					LabelAccess access = (LabelAccess) item;
					QnxLabel label = getQnxLabel(access.getData());
					
					if (access.getAccess() == LabelAccessEnum.READ) {			// Label READ access
						tmpRunnable.addLabelRead(label);
					} else if (access.getAccess() == LabelAccessEnum.WRITE) {	// Label WRITE access
						tmpRunnable.addLabelWrite(label);
					}
					
				} else if (item instanceof Ticks) {
					
					Ticks ticks = (Ticks) item;
					long wcet = ticks.getDefault().getUpperBound();
					if (!tmpRunnable.addMode(0, wcet)) {
						System.err.println("Could not add a mode to runnable " + tmpRunnable.getName());
						System.exit(1);
					}
					
				} else if (item instanceof Switch) {
					
					Switch modeSwitch = (Switch) item;
					
					for (SwitchEntry entry : modeSwitch.getEntries()) {
						try {
							int cond = Integer.parseInt(entry.getName());
							
							if (entry.getItems().size() != 1) {
								System.err.println("Switch entry of runnable " + tmpRunnable.getName() + " has more than one entry in its call graph.");
								System.exit(1);
							}
							else {
								if (entry.getItems().get(0) instanceof Ticks) {
									Ticks ticks = (Ticks) entry.getItems().get(0);
									long wcet = ticks.getDefault().getUpperBound();
									
									if (!tmpRunnable.addMode(cond, wcet)) {
										System.err.println("Could not add a mode to runnable " + tmpRunnable.getName());
										System.exit(1);
									}
								}
							}
							
						} catch(NumberFormatException e){ 
							System.err.println("Could not pare condition for Switch statement of runnable " + tmpRunnable.getName());
							System.exit(1);
						}
					}
				}
				else {
					System.err.println("Item type not supported -> " + item);
					System.exit(1);
				}
			}
			system.addRunnable(tmpRunnable);
		}
	}
	
	/**
	 * Method parses all tasks from the model and adds them to the system.
	 */
	private static void parseTasks() {
		for (Task t : model.getSwModel().getTasks()) {
			
			String name = t.getName();
			long period = getTaskPeriod(t);
			
			QnxTask tmpTask = new QnxTask(name, period);
			
			if (t.getActivityGraph().getItems().size() != 1) {
				System.err.println("Task " + name + " has more than one item in its activity graph.");
				System.exit(1);
			} else {
				if (!(t.getActivityGraph().getItems().get(0) instanceof Group)) {
					System.err.println("Task " + name + " implements no execution sequence.");
					System.exit(1);
				} else {
					Group group = (Group) t.getActivityGraph().getItems().get(0);
					
					for (ActivityGraphItem activity : group.getItems()) {
						if (activity instanceof RunnableCall) {
							RunnableCall call = (RunnableCall) activity;
							
							QnxRunnable tmpRunnable = getQnxRunnable(call.getRunnable());
							
							tmpTask.addRunnable(tmpRunnable);
						}
					}
				}
			}
			system.addTask(tmpTask);
		}
	}
	
	/**
	 * Method parses the hardware model.
	 */
	private static void parseHardware() {
		HWModel hw = model.getHwModel();
		
		if (hw.getStructures().size() != 1) {
			System.err.println("Hardware structure should have only one top-level element.");
			System.exit(1);
		}
		if (hw.getStructures().get(0).getStructureType() != StructureType.SYSTEM) {
			System.err.println("Top-level element of the hardware structure must be of type SYSTEM");
			System.exit(1);
		}
		
		HwStructure sys = hw.getStructures().get(0);
		
		
		
		for (HwStructure structure : sys.getStructures()) {	// Parse all ECU/nodes
			if (structure.getStructureType() != StructureType.ECU) {
				System.err.println("Second-level hardware elements must be of type ECU.");
				System.exit(1);
			}
			
			String name = structure.getName();
			
			ArrayList<Core> tmpCores = new ArrayList<Core>();
			int idCount = 0;
			
			String ip = getNodeIP(structure);
			
			long frequency_hz = -1;
			
			for (HwModule module : structure.getModules()) {
				if (module instanceof ProcessingUnit) {
					
					ProcessingUnit cpu = (ProcessingUnit) module;
					
					tmpCores.add(new Core(cpu.getName(), idCount));
					idCount++;
					
					double value = cpu.getFrequencyDomain().getDefaultValue().getValue();
					FrequencyUnit unit = cpu.getFrequencyDomain().getDefaultValue().getUnit();
					
					long tmpFrequency_hz = 0;
					if (unit == FrequencyUnit.GHZ) {
						tmpFrequency_hz = (long) (value * 1000000000.0);
					} else if (unit == FrequencyUnit.MHZ) {
						tmpFrequency_hz = (long) (value * 1000000.0);
					} else if (unit == FrequencyUnit.KHZ) {
						tmpFrequency_hz = (long) (value * 1000.0);
					} else if (unit == FrequencyUnit.HZ) {
						tmpFrequency_hz = (long) value;
					}
					
					if (frequency_hz > -1) {
						if (frequency_hz != tmpFrequency_hz) {
							System.err.println("Not all cores of the node have the same frequency!");
							System.exit(1);
						}
					} else {
						frequency_hz = tmpFrequency_hz;
					}
				}
			}
			
			QnxNode tmpNode = new QnxNode(name, frequency_hz);
			tmpNode.setIpAddress(ip);
			
			for (Core c : tmpCores) {
				tmpNode.addCpu(c);
			}
			
			system.addNode(tmpNode);
		}
	}
	
	/**
	 * Method parses the OS model.
	 */
	private static void parseOs() {
		OSModel osModel = model.getOsModel();
		
		for (OperatingSystem os : osModel.getOperatingSystems()) {
			
			ProcessingUnit pu = null;

			TaskScheduler fppsScheduler = null;
			
			int apsWindowSize = 0;
			
			for (TaskScheduler sched : os.getTaskSchedulers()) {	// Find the responsible core for the scheduler
				if (sched.getDefinition().getName().equals("FixedPriorityPreemptive")) {
					fppsScheduler = sched;
					
					apsWindowSize = ((IntegerObject)sched.getCustomProperties().get("APS_WindowSize")).getValue();
					
					for (SchedulerAllocation alloc : model.getMappingModel().getSchedulerAllocation()) {
						if (alloc.getScheduler() == fppsScheduler) {
							pu = alloc.getExecutingPU();
							break;
						}
					}
				}
			}
			
			QnxNode node = null;
			
			for (QnxNode n : system.getNodes()) {	// Find the node that hosts the core
				for (Core c : n.getCores()) {
					if (c.getName().equals(pu.getName())) {
						node = n;
					}
				}
			}
			
			if (node == null) {
				System.err.println("Could not find the node the scheduler with core " + pu.getName() + " is allocated to");
				System.exit(1);
			}
			
			node.setApsWindowsizeMs(apsWindowSize);	// Set the APS window size of the node
			
			// Find all APS partitions
			for (TaskScheduler sched : os.getTaskSchedulers()) {
				if (sched.getParentScheduler() == fppsScheduler) {	// The APS partitions must be linked to the FPPS scheduler
					if (sched.getDefinition().getName().equals("APSPartition")) {
						int budget = ((IntegerObject)sched.getCustomProperties().get("Budget")).getValue();
						String name = sched.getName();
						int budgetPercentScale = ((IntegerObject)sched.getCustomProperties().get("BudgetPercentScale")).getValue();
						
						if (budgetPercentScale > 1) {
							// It seems only values of 0 and 1 are allowed, other values lead to 'invalid argument' errors when configuring the APS partitions.
							System.err.println("BudgetPercentScale must be 0 or 1");
							System.exit(1);
						}
						
						node.addPartition(new ApsPartition(name, budget, budgetPercentScale, false));
					}
				}
			}
		}
	}
	
	/*
	 * Method parses the task allocation.
	 */
	private static void parseTaskAllocation() {
		
		ArrayList<Integer> usedPriorities = new ArrayList<Integer>();
		
		for (TaskAllocation alloc : model.getMappingModel().getTaskAllocation()) {
						
			QnxTask task = system.findTaskByName(alloc.getTask().getName());
			ApsPartition partition = null;
			
			QnxNode node = null;
			
			if (alloc.getScheduler().getDefinition().getName().equals("FixedPriorityPreemptive")) {
				// If the task is allocated to the FPPS scheduler we must assign the task to the System Partition.
				
				// Find the scheduler allocation for the FPPS scheduler in order to identify the node it is mapped to
				SchedulerAllocation schedAlloc = null;
				for (SchedulerAllocation tmp : model.getMappingModel().getSchedulerAllocation()) {
					if (tmp.getScheduler() == alloc.getScheduler()) {
						schedAlloc = tmp;
						break;
					}
				}
				ProcessingUnit pu = schedAlloc.getExecutingPU();
				
				node = null;
				
				for (QnxNode n : system.getNodes()) {	// Find the node that hosts the core
					for (Core c : n.getCores()) {
						if (c.getName().equals(pu.getName())) {
							node = n;
						}
					}
				}
				partition = node.getSystemPartition();
				
			} else if (alloc.getScheduler().getDefinition().getName().equals("APSPartition")) {
				// If the task is allocated to one of the APS partitions we can assign it directly to this partition.
				
				if (alloc.getScheduler().getParentScheduler() != null) {
					
					SchedulerAllocation schedAlloc = null;
					for (SchedulerAllocation tmp : model.getMappingModel().getSchedulerAllocation()) {
						if (tmp.getScheduler() == alloc.getScheduler().getParentScheduler()) {
							schedAlloc = tmp;
							break;
						}
					}
					ProcessingUnit pu = schedAlloc.getExecutingPU();
					
					node = null;
					
					for (QnxNode n : system.getNodes()) {	// Find the node that hosts the core
						for (Core c : n.getCores()) {
							if (c.getName().equals(pu.getName())) {
								node = n;
							}
						}
					}
					
					partition = node.getPartitionByName(alloc.getScheduler().getName());
					
				} else {
					System.err.println("APS scheduler " + alloc.getScheduler().getName() + " has no parent scheduler.");
					System.exit(1);
				}
			} else {
				System.err.println("Scheduler must be of type FixedPriorityPreemptive or APSPartition.");
				System.exit(1);
			}
			
			// In both cases the allocation also indicated the core affinities which must be parsed next.
			for (ProcessingUnit pu : alloc.getAffinity()) {
				for (Core c : node.getCores()) {
					if (c.getName().equals(pu.getName())) {
						task.addCoreToAffinity(c);
					}
				}
			}
			
			// Making sure that the task and partition could be found.
			if (task == null) {
				System.err.println("Could not find the task with name " + alloc.getTask().getName()); 
				System.exit(1);
			}
			if (partition == null) {
				System.err.println("Could not find the scheduler with name " + alloc.getScheduler().getName()); 
				System.exit(1);
			}
				
			/**
			 * Assign the task priority for each task
			 */
			int priority = -1;
			for (Entry<SchedulingParameterDefinition, Value> param : alloc.getSchedulingParameters()) {
				if (param.getKey().getName().equals("priority")) {
					priority = ((IntegerObject)param.getValue()).getValue();
				}
			}
			if (priority == -1) {
				System.err.println("No task priority set for task " + task.getName());
				System.exit(1);
			}
			if (usedPriorities.contains(priority)) {
				System.err.println("Tasks must have a unique priority! Priority " + priority + " assigned more than once. Last to task " + task.getName());
				System.exit(1);
			} else {
				usedPriorities.add(priority);
			}
			task.setPriority(priority);
			
			partition.addTask(task);	// Assign the task to the partition
		}
	}
	
	/**
	 * Method to parse the task constraints. 
	 * So far we support task deadlines (i.e. upper bounds on a task's response time).
	 */
	private static void parseConstraints() {
		ConstraintsModel constraints = model.getConstraintsModel();
		
		if (constraints != null) {	// This might be null if no deadlines are specified
			for (Requirement req : constraints.getRequirements()) {
				
				if (req instanceof ProcessRequirement) {
					
					ProcessRequirement prosReq = (ProcessRequirement)req;
					
					if (prosReq.getProcess() instanceof Task) {
						if (prosReq.getLimit().getLimitType() == LimitType.UPPER_LIMIT) {
							TimeRequirementLimit limit = (TimeRequirementLimit)prosReq.getLimit();
							if (limit.getMetric() == TimeMetric.RESPONSE_TIME) {
								
								
								BigInteger value = limit.getLimitValue().getValue();
								TimeUnit unit = limit.getLimitValue().getUnit();
								
								long deadline_ms = 0;
								if (unit == TimeUnit.MS) {
									deadline_ms = value.intValueExact();
								} else if (unit == TimeUnit.S) {
									deadline_ms = value.intValueExact() * 1000;
								} else {
									System.err.println("The period value for a deadline constraint must be in units of ms or larger, have" + unit + ".");
									System.exit(1);
								}
								
								QnxTask task = null;
								for (QnxTask tmpTask : system.getTasks()) {
									if(tmpTask.getName().equals(((Task)prosReq.getProcess()).getName())) {
										task = tmpTask;
									}
								}
								if (task != null) {
									task.setDeadline_ms(deadline_ms);
									task.setCriticality(severityToInt(prosReq.getSeverity()));
								} else {
									System.err.println("Cound not find task " + ((Task)prosReq.getProcess()).getName() + " for deadline constraint.");
									System.exit(1);
								}
								
							} else {
								System.err.println("A requirement of an unsupported type is specified.\nSo far only process requirements of type upper limit and response time are supported.");
								System.exit(1);
							}
						} else {
							System.err.println("A requirement of an unsupported type is specified.\nSo far only process requirements of type upper limit and response time are supported.");
							System.exit(1);
						}
					} else {
						System.err.println("Requirement is specified for an object of class " + prosReq.getProcess().getClass() + " but only requirements on Task objects are supported at the moment.");
						System.exit(1);
					}
				}
			}
		}
	}
	
	/**
	 * Helper method to translate a severity value into an integer. 
	 * Smaller values indicate a larger severity.
	 * @param severity Severity of the requirement.
	 * @return Integer value, smaller equals higher severity.
	 */
	private static int severityToInt(Severity severity) {
		if (severity == Severity.CRITICAL) {
			return 0;
		} else if (severity == Severity.MAJOR) {
			return 1;
		} else if (severity == Severity.MINOR) {
			return 2;
		} else if (severity == Severity.COSMETIC) {
			return 3;
		} 
		return -1;
	}

	/**
	 * Helper method to translate an ASIL level into an integer. 
	 * Smaller values indicate a larger severity.
	 * @param asil ASIL level of the runnable.
	 * @return Integer value, smaller equals higher severity.
	 */
	private static int asilToInt(ASILType asil) {
		
		if (asil == ASILType.D) {
			return 0;
		} else if (asil == ASILType.C) {
			return 1;
		} else if (asil == ASILType.B) {
			return 2;
		} else if (asil == ASILType.A) {
			return 3;
		} else if (asil == ASILType.QM) {
			return 4;
		} 
 
		return 0;
	}
	
	/**
	 * Generate all required communication channels.
	 */
	public static void generateCommunicationChannels() {
		
		ArrayList<QnxTask> tmpListenerTaskList = new ArrayList<QnxTask>();
		
		for (QnxTask task : system.getTasks()) {
			// Find all tasks that read from a label which is written by this task
			ArrayList<QnxTask> receiverTasks = new ArrayList<QnxTask>();
			
			for (QnxLabel label : task.getAllWriteLabels()) {
				for (QnxTask tmpTask : system.getTasks()) {
					if (tmpTask != task) {
						if (tmpTask.getAllReadLabels().contains(label)) {
							receiverTasks.add(tmpTask);
						}
					}
				}
			}
			
			// Get the list of nodes on which the consumer tasks are allocated
			ArrayList<QnxNode> receiverNodes = new ArrayList<QnxNode>();
			
			for (QnxTask tmpTask : receiverTasks) {
				QnxNode tmpNode = tmpTask.getPartition().getNode();
				
				if (tmpNode != task.getPartition().getNode()) {
					if (!receiverNodes.contains(tmpNode)) receiverNodes.add(tmpNode);
				}
			}
			
			// Create a channel to each of the consumer nodes
			for (QnxNode tmpNode : receiverNodes) {
				
				// Create listener task on the receiving node
				QnxTask listener = QnxTask.createListenerTask(task, tmpNode);
				tmpListenerTaskList.add(listener);
				
				// Create the channel and link it to sender and receiver task
				String channelName = task.getName() + "_to_" + tmpNode.getName();
				QnxComChannel channel = new QnxComChannel(channelName);
				channel.setSender(task);
				channel.setReceiver(listener);
				
				// Register the channel with the nodes they are connected with
				task.getPartition().getNode().addChannel(channel);
				listener.getPartition().getNode().addChannel(channel);
				
				ArrayList<QnxTask> receiverTasksOnNode = new ArrayList<QnxTask>();
				
				// Get all tasks that receive data from the sender task on this node
				for (QnxTask tmpTask : receiverTasks) {
					if (tmpTask.getPartition().getNode() == tmpNode) {
						receiverTasksOnNode.add(tmpTask);
					}
				}
				
				// Add all labels that are received by any of the tasks on this node to the channel.
				for (QnxLabel label : task.getAllWriteLabels()) {
					for (QnxTask tmpTask : receiverTasksOnNode) {
						for (QnxLabel tmpLabel : tmpTask.getAllReadLabels()) {
							if (label == tmpLabel) {
								channel.addLabel(label);
							}
						}
					}
				}
				
				// Create the sender and receiver runnable and add them to the respective tasks
				QnxRunnable senderRunnable = new QnxRunnable("Tx_" + channel.getName(), QnxRunnableType.SENDER_RUNNABLE);
				QnxRunnable receiverRunnable = new QnxRunnable("Rx_" + channel.getName(), QnxRunnableType.RECEIVER_RUNNABLE);
				
				senderRunnable.setChannel(channel);
				receiverRunnable.setChannel(channel);
				
				for (QnxLabel label : channel.getLabels()) {
					senderRunnable.addLabelRead(label);
					receiverRunnable.addLabelWrite(label);
				}
				
				task.addRunnable(senderRunnable);
				listener.addRunnable(receiverRunnable);
			}
			
		}
		
		// Add all listener tasks here
		for (QnxTask t : tmpListenerTaskList) {
			system.addTask(t);
		}
	}
	
	/**
	 * Get the IP of this node. This is added to the port as custom property.
	 * We require each node to have exactly one IP address!
	 * @param ecu
	 * @return
	 */
	public static String getNodeIP(HwStructure ecu) {
		
		String ip = "";
		
		for (HwPort p : ecu.getPorts()) {
			ip = ((StringObjectImpl)p.getCustomProperties().get("IP")).getValue();
		}
		
		return ip;
	}
	
	/**
	 * Get the periodic activation rate of a task.
	 * @param task Amalthea task.
	 * @return Periodic activation rate in ms. 
	 */
	public static long getTaskPeriod(Task task) {
		
		long period_ms = 0;
		PeriodicStimulus pStimuli = null;
		
		for (Stimulus s : task.getStimuli()) {
			if (s instanceof PeriodicStimulusImpl) {
				if (pStimuli == null) {
					pStimuli = (PeriodicStimulusImpl)s;
					
					BigInteger value = pStimuli.getRecurrence().getValue();
					TimeUnit unit = pStimuli.getRecurrence().getUnit();
					
					if (unit == TimeUnit.MS) {
						period_ms = value.intValueExact();
					} else if (unit == TimeUnit.S) {
						period_ms = value.intValueExact() * 1000;
					} else {
						System.err.println("Period value must be in units of ms or larger.");
					}
				} else {
					System.err.println("Task " + task.getName() + " has more than one periodic stimuli!");
				}
			}
		}
		
		return period_ms;
	}

	/**
	 * Helper method to return the QNX label that represents a given Amalthea label.
	 * @param _label Amalthea label.
	 * @return QNX label.
	 */
	private static QnxLabel getQnxLabel(Label _label) {
		for (QnxLabel l : system.getLabels()) {
			if (l.getName().equals(_label.getName())) {
				return l;
			}
		}
		return null;
	}
	
	/**
	 * Helper function to return the QNX runnable that represents a given Amalthea runnable.
	 * @param _runnable Amalthea runnable.
	 * @return Qnx runnable.
	 */
	private static QnxRunnable getQnxRunnable(Runnable _runnable) {
		for (QnxRunnable r : system.getRunnables()) {
			if (r.getName().equals(_runnable.getName())) {
				return r;
			}
		}
		return null;
	}
	
	/**
	 * Helper method to print all labels of the system.
	 */
	public static void printAllLabels() {
		for (QnxLabel l : system.getLabels()) {
			System.out.println(l);
		}
	}
	
	/**
	 * Helper method to print all runnables of the system.
	 */
	public static void printAllRunnables() {
		for (QnxRunnable r : system.getRunnables()) {
			System.out.println(r);
		}
	}
	
	/**
	 * Helper method to print all tasks of the system.
	 */
	public static void printAllTasks() {
		for (QnxTask t : system.getTasks()) {
			System.out.println(t);
		}
	}
	
	public static void printPlatform() {
		System.out.println(system.print());
	}
	
	/**
	 * Method loads an Amalthea model from separate files
	 * @param _folder Folder with model files.
	 * @return Combined Amalthea model.
	 */
	public static Amalthea loadModel(String _folder) {
		final File inputFolder = new File(_folder);
		final AmaltheaFactory fac = AmaltheaFactory.eINSTANCE;

		Amalthea model = fac.createAmalthea();
		
		ResourceSet resourceSet = AmaltheaLoader.loadFromDirectory(inputFolder);
		
		if (resourceSet != null) {
			System.out.println("Reading files from directory: " + inputFolder.getAbsolutePath());
		} else {
			System.err.println("Error: No model loaded!");
			return null;
		}

		Collection<Amalthea> models = AmaltheaLoader.collectAmaltheaModels(resourceSet);
		
		for (Amalthea a : models) {
			if (a.getSwModel() != null) {
				model.setSwModel(a.getSwModel());
				a.setSwModel(null);
			}
			
			if (a.getStimuliModel() != null) {
				model.setStimuliModel(a.getStimuliModel());
				a.setStimuliModel(null);
			}
			
			if (a.getHwModel() != null) {
				model.setHwModel(a.getHwModel());
				a.setHwModel(null);
			}
			
			if (a.getOsModel() != null) {
				model.setOsModel(a.getOsModel());
				a.setOsModel(null);
			}
			
			if (a.getMappingModel() != null) {
				model.setMappingModel(a.getMappingModel());
				a.setMappingModel(null);
			}
			
			if (a.getConstraintsModel() != null) {
				model.setConstraintsModel(a.getConstraintsModel());
				a.setConstraintsModel(null);
			}
		}
		
		return model;
	}
}
