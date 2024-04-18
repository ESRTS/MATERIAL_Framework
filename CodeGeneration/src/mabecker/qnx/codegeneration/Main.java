package mabecker.qnx.codegeneration;

import mabecker.qnx.codegeneration.model.EdgeSystem;
import mabecker.qnx.codegeneration.model.Parser;


public class Main {

	private final static int WATERS2019_PARTITIONED = 1;		// Selects the WATERS 2019 case study under partitioned scheduling 
	private final static int WATERS2019_GLOBAL = 9;				// Selects the WATERS 2019 case study under global scheduling
	private final static int WATERS2019_APS = 10;				// Selects the WATERS 2019 case study under partitioned scheduling and APS reservations on node 2
	private final static int BBW_SINGLE_NODE_FPPS = 2;			// Selects the BBW case study under FPPS on a single node
	private final static int BBW_DISTRIBUTED_FPPS = 3;			// Selects the BBW case study under FPPS distributed on two nodes
	private final static int BBW_SINGLE_GLOBALSCHED_1CPU = 4;	// Selects the BBW case study on a single node with global scheduling and 1 CPU
	private final static int BBW_SINGLE_GLOBALSCHED_2CPU = 5;	// Selects the BBW case study on a single node with global scheduling and 2 CPU
	private final static int BBW_SINGLE_GLOBALSCHED_3CPU = 6;	// Selects the BBW case study on a single node with global scheduling and 3 CPU
	private final static int BBW_SINGLE_GLOBALSCHED_4CPU = 7;	// Selects the BBW case study on a single node with global scheduling and 4 CPU
	private final static int TEST = 8;							// Selects a simple test scenario with two communicating tasks on two nodes
	
	public static void main(String[] args) {		
		boolean COMPILE = true;		// Set to true to automatically compile the projects.
		boolean TRANSFER = false;	// Set to true to automatically transfer the executables to the QNX nodes.
		
		int selectedExperiment = WATERS2019_PARTITIONED;	// Select the project here. This could also be an argument to the program...
		
		String inputFolder = null;
		String modelName = null;
		
		switch (selectedExperiment) {
		case WATERS2019_PARTITIONED:
			inputFolder = "../Examples/model_WATERS2019_Partitioned";
			modelName = "WATERS2019_Partitioned";
			break;
		case WATERS2019_GLOBAL:
			inputFolder = "../Examples/model_WATERS2019_Global";
			modelName = "WATERS2019_Global";
			break;
		case WATERS2019_APS:
			inputFolder = "../Examples/model_WATERS2019_APS";
			modelName = "WATERS2019_APS";
			break;
		case BBW_SINGLE_NODE_FPPS:
			inputFolder = "../Examples/model_BBW_local";
			modelName = "RPI_BBW_local";
			break;
		case BBW_DISTRIBUTED_FPPS:
			inputFolder = "../Examples/model_BBW_distributed";
			modelName = "RPI_BBW_distributed";
			break;
		case BBW_SINGLE_GLOBALSCHED_1CPU:
			inputFolder = "../Examples/model_BBW_local_Global1core";
			modelName = "RPI_BBW_local_1core";
			break;
		case BBW_SINGLE_GLOBALSCHED_2CPU:
			inputFolder = "../Examples/model_BBW_local_Global2core";
			modelName = "RPI_BBW_local_2core";
			break;
		case BBW_SINGLE_GLOBALSCHED_3CPU:
			inputFolder = "../Examples/model_BBW_local_Global3core";
			modelName = "RPI_BBW_local_3core";
			break;
		case BBW_SINGLE_GLOBALSCHED_4CPU:
			inputFolder = "../Examples/model_BBW_local_Global4core";
			modelName = "RPI_BBW_local_4core";
			break;
		case TEST:
			inputFolder = "../Examples/model_test";
			modelName = "Test_Model";
			break;
		default:
			break;
		}
		
		/**
		 * Parse the input model and generate the internal representation to describe the edge system.
		 */
		
		EdgeSystem system = Parser.parse(modelName, inputFolder);
		
		/**
		 * Generate the code for each node of the edge system.
		 */
		Generator.generateCode(system, "../TargetProject/" + modelName, COMPILE, TRANSFER);
	}
	
}
