package mabecker.qnx.codegeneration.model;

import java.util.ArrayList;

public class QnxNode {

	private ArrayList<ApsPartition> 	partitions;			// APS partitions of this node
	private int 						apsWindowsizeMs;	// APS window size in ms
	private EdgeSystem 					system;				// Edge system this node belongs to
	private String 						ipAddress;			// IP address of this node
	private ArrayList<Core> 			cores;				// List of (homogeneous) cores of the node
	private long						ticksPerSecond;		// Number of ticks computed per second (assuming one CPU cycle is one tick)
	private String						name;				// Name of the core
	private ArrayList<QnxComChannel>	channels;			// All QNX communication channels of this node
	
	/**
	 * Create a new QNX node.
	 * @param _system The edge system the node belongs to.
	 * @param _numCpu Number of homogeneous CPUs.
	 * @param _ticksPerSecond Speed of the CPUs in ticks per second.
	 */
	public QnxNode(String _name, long _ticksPerSecond) {
		name = _name;
		partitions = new ArrayList<ApsPartition>();
		apsWindowsizeMs = 100;	// Default window size in QNX is 100ms
		system = null;
		ipAddress = null;
		channels = new ArrayList<QnxComChannel>();
		
		ticksPerSecond = _ticksPerSecond;
		
		cores = new ArrayList<Core>();
		
		addSystemPartition();
	}
	
	public void addCpu(Core _core) {
		if (!cores.contains(_core)) {
			cores.add(_core);
			_core.addNode(this);
		}
	}
	
	/**
	 * Get the name of the core.
	 * @return Name string.
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * Register the edge system the node belongs to.
	 * @param _system Edge system of the node.
	 */
	public void addSystem(EdgeSystem _system) {
		system = _system;
	}
	
	/**
	 * Get the system the node belongs to.
	 * @return Edge system of the node.
	 */
	public EdgeSystem getSystem() {
		return system;
	}
	
	/**
	 * Return the APS window size in ms.
	 * @return APS window size in ms.
	 */
	public int getApsWindowsizeMs() {
		return apsWindowsizeMs;
	}
	
	/**
	 * Method to set a new APS window size. Default value is 100ms.
	 * @param apsWindowsizeMs Window size in ms.
	 */
	public void setApsWindowsizeMs(int apsWindowsizeMs) {
		this.apsWindowsizeMs = apsWindowsizeMs;
	}
	
	/**
	 * Register an IP address for this node.
	 * @param ipAddress IP address of the node.
	 */
	public void setIpAddress(String ipAddress) {
		this.ipAddress = ipAddress;
	}
	
	/**
	 * Get the IP address of the node.
	 * @return	IP address string. 
	 */
	public String getIpAddress() {
		return ipAddress;
	}
	
	/**
	 * Get the speed of the different cores in ticks per second
	 * @return returns ticks per second.
	 */
	public long getTicksPerSecond() {
		return ticksPerSecond;
	}
	
	/**
	 * Method to add the system partition to the node.
	 */
	private void addSystemPartition() {
		ApsPartition sysPartition = new ApsPartition("System Partition", 100, 0, true);	// The system partition initially contains all budget
		addPartition(sysPartition);
	}
	
	/**
	 * Return the system partition.
	 * @return System partition.
	 */
	public ApsPartition getSystemPartition() {
		for (ApsPartition p : partitions) {
			if (p.isSystemPartition() == true) return p;
		}
		return null;
	}
	
	/**
	 * Method to add a new APS partition to the node.
	 * @param _partition APS partition.
	 */
	public void addPartition(ApsPartition _partition) {
		if (!partitions.contains(_partition)) {
			
			// Add the new partition to the node
			partitions.add(_partition);
			_partition.addNode(this);
			
			// In case of a user partition we have to resize the system partition's budget
			if (_partition.isSystemPartition() == false) {
				ApsPartition sysPartition = getSystemPartition();
			
				/**
				 * To keep track of the different budgets and to compute the remaining budget for the system partition,
				 * the configured budgets for the different partitions are reconfigured to all use the same (maximum)
				 * budget percentage scaling factor. 
				 */
				
				// Find the largest current budgetPercentageScale value
				int maxBudgetPercentageScale = 0;
				for (ApsPartition p : partitions) {
					if (p.getBudgetPercentageScale() > maxBudgetPercentageScale) {
						maxBudgetPercentageScale = p.getBudgetPercentageScale();
					}
				}
				
				// Reconfigure each partition to use the maxBudgetPercentageScale value
				for (ApsPartition p : partitions) {
					int diff = maxBudgetPercentageScale - p.getBudgetPercentageScale();
					if (diff > 0) {
						while (diff > 0) {
							p.setBudgetPercent(p.getBudgetPercent() * 10);
							diff--;
						}
					}
					p.setBudgetPercentageScale(maxBudgetPercentageScale);
				}
				
				// Get the max user budget
				int sumUserBudget = 0;
				for (ApsPartition p : partitions) {
					if (!p.isSystemPartition()) {
						sumUserBudget += p.getBudgetPercent();
					}
				}
				
				// Compute the value for 100% budget considering the current BudgetPercentageScale
				int tmp = maxBudgetPercentageScale;
				int fullBudget = 100;
				while (tmp > 0) {
					fullBudget = fullBudget * 10;
					tmp--;
				}
				
				// Set the remaining budget for the system partition
				int systemBudget = fullBudget - sumUserBudget;
				
				// Check that the remaining budget was not negative and configure the system partition
				if (systemBudget < 0) {
					System.err.println("System Budget must be > 0. It is: " + systemBudget);
					System.exit(0);
				}
				sysPartition.setBudgetPercent(fullBudget - sumUserBudget);
			}
		}
	}
	
	/**
	 * Returns the cores of the node;
	 * @return List of cores.
	 */
	public ArrayList<Core> getCores() {
		return cores;
	}
	
	@Override
	public String toString() {
		String output = "Node: " + name + " Frequency: " + ticksPerSecond + "Hz IP: " + ipAddress + " APS Window Size: " + apsWindowsizeMs + "ms";
		
		return output;
	}

	/**
	 * Method returns the APS partition with the given name
	 * @param _name Name of the partition.
	 * @return ApsPartition of the given name.
	 */
	public ApsPartition getPartitionByName(String _name) {
		
		for (ApsPartition p : partitions) {
			if (p.getName().equals(_name)) return p;
		}
		return null;
	}
	
	/**
	 * Method returns a list of all tasks on this node.
	 * @return List of tasks.
	 */
	public ArrayList<QnxTask> getAllTasks() {
		ArrayList<QnxTask> nodeTasks = new ArrayList<QnxTask>();
		
		for (ApsPartition p : partitions) {
			for (QnxTask t : p.getTasks()) {
				if (!nodeTasks.contains(t)) {
					nodeTasks.add(t);
				}
			}
		}
		
		return nodeTasks;
	}
	
	/**
	 * Method returns a list of all runnables executed by tasks on this node.
	 * @return List of runnables.
	 */
	public ArrayList<QnxRunnable> getAllRunnables() {
		ArrayList<QnxRunnable> nodeRunnables = new ArrayList<QnxRunnable>();
		
		for (ApsPartition p : partitions) {
			for (QnxTask t : p.getTasks()) {
				for (QnxRunnable r : t.getRunnables()) {
					if (!nodeRunnables.contains(r)) {
						nodeRunnables.add(r);
					}
				}
			}
		}
		
		return nodeRunnables;
	}
	
	/**
	 * Return all APS partitions.
	 * @return List of all partitions.
	 */
	public ArrayList<ApsPartition> getPartitions() {
		return partitions;
	}

	public String print() {
		String output = this.toString() + "\n";
		for (Core c : cores) {
			output += "\tCore: " + c + "\n";
		}
		
		for (ApsPartition p : partitions) {
			output += "\tAPS Partition: " + p + "\n";
			for (QnxTask t : p.getTasks()) {
				output += "\t\tTask: " + t.getName() + " [";
				for (int i = 0; i < t.getCoreAffinity().size(); i++) {
					Core c = t.getCoreAffinity().get(i);
					output += c.getName();
					if (i < t.getCoreAffinity().size()-1) {
						output += ", ";
					}
				}
				output += "] Priority: " + t.getPriority();
				output += ", Period: " + t.getPeriod_ms();
				output += "ms, Deadline: " + t.getDeadline_ms();
				output += "ms, Criticality: " + t.getCriticality() + "\n";
				for (QnxRunnable r : t.getRunnables()) {
					output += "\t\t\t" + r.toString() + " Criticality: " + r.getCriticality() + "\n";
					
					// All read labels
					for (QnxLabel l : r.getReadLabels()) {
						output += "\t\t\t\t Read: " + l.getName() + "\n";
					}
					
					// All modes
					for (QnxMode m : r.getModes()) {
						output += "\t\t\t\t Mode: " + m.getCondition() + " -> " + m.getExecutionTicks() + "[ticks]\n";
					}
					
					// All write labels
					for (QnxLabel l : r.getWriteLabels()) {
						output += "\t\t\t\t Write: " + l.getName() + "\n";
					}
				}
			}
		}
		return output;
	}
	
	/**
	 * Returns all communication channels used by this node.
	 * @return
	 */
	public ArrayList<QnxComChannel> getAllChannels() {
		return channels;
	}
	
	/**
	 * Add a new channel to this node. 
	 * @param _channel New channel to add.
	 */
	public void addChannel(QnxComChannel _channel) {
		if (!channels.contains(_channel)) {
			channels.add(_channel);
		}
	}
}
