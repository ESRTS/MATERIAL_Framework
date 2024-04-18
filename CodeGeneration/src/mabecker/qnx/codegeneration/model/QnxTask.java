package mabecker.qnx.codegeneration.model;

import java.util.ArrayList;

public class QnxTask {

	private ArrayList<QnxRunnable> 		runnables;		// List of all runnabels assigned to this task
	private ApsPartition				partition;		// The APS partition the task is mapped to
	private ArrayList<Core>				coreAffinity;	// List of cores the task can run on
	private String						name;			// Name of the task
	private long						period_ms;		// Period of the task in ms
	private long 						deadline_ms;	// Deadline of the task in ms
	private int 						priority;		// Task priority
	private int							criticality;	// Criticality of the task,  smaller values indicate a larger criticality
	private boolean						isListenerTask;	// Flag to indicate if this is a listener task
	private ArrayList<QnxComChannel>	senderChannels;	// List of all channels the task sends to
	
	/**
	 * Create a new empty task.
	 * @param _name Name of the task
	 */
	public QnxTask(String _name, long _period_ms) {
		name = _name;
		runnables = new ArrayList<QnxRunnable>();
		coreAffinity = new ArrayList<Core>();
		partition = null;
		period_ms = _period_ms;
		deadline_ms = _period_ms;	// by default each task has an implicit deadline
		priority = -1;
		criticality = 0;			// critical if not specified different later on
		isListenerTask = false;
		senderChannels = new ArrayList<QnxComChannel>();
	}
	
	/**
	 * Method to check if this is a listener task.
	 * @return True if this is a listener task and false otherwise.
	 */
	public boolean isListenerTask() {
		return isListenerTask;
	}
	
	/**
	 * This method is used to create a listener task based on a sender task and a given destination node.
	 * The task will be automatically allocated to the system partition of the destination node and scheduled
	 * and scheduled at the priority of the sender task.
	 * @param _senderTask Source for the listener task.
	 * @param _destination Destination node to allocate the listener task.
	 */
	public static QnxTask createListenerTask(QnxTask _senderTask, QnxNode _destination) {
		QnxTask listener = new QnxTask("Listener_" + _senderTask.getName(), -1);
		listener.isListenerTask = true;
		listener.priority = _senderTask.priority;
		
		// Get the destination core
		Core dstCore =  null;
		for (Core c : _destination.getCores()) {
			if (c.getId() == 0) {
				dstCore = c;
				break;
			}
		}
		
		/**
		 * A listener task is allocated to core 0 of the destination node and executed by the system partition.
		 */
		listener.addCoreToAffinity(dstCore);
		_destination.getSystemPartition().addTask(listener);
		
		return listener; 
	}
	
	/**
	 * Get the core affinity of the task.
	 * @return List of cores the task can execute on.
	 */
	public ArrayList<Core> getCoreAffinity() {
		return coreAffinity;
	}
	
	/**
	 * Method to read the task priority. Larger values indicate a higher priority. Values between 1 and 255.
	 * @return Task priority.
	 */
	public int getPriority() {
		return priority;
	}
	
	/**
	 * Add a core to the task's core affinity.
	 * @param _core Core to execute the task.
	 */
	public void addCoreToAffinity(Core _core) {
		coreAffinity.add(_core);
	}
	
	/**
	 * Get the name of the task.
	 * @return Name string.
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * Get the APS partition the task is allocated to.
	 * @return APS partition the task executes in.
	 */
	public ApsPartition getPartition() {
		return partition;
	}
	
	/**
	 * Set the partition the task is allocated to.
	 * @param partition APS partition the task executes in.
	 */
	public void setPartition(ApsPartition partition) {
		this.partition = partition;
	}
	
	/**
	 * Get the activation period of the task.
	 * @return Activation period in ms.
	 */
	public long getPeriod_ms() {
		return period_ms;
	}
	
	/**
	 * Get the sequence of runnables that are executed by the task.
	 * @return Runnables of the task.
	 */
	public ArrayList<QnxRunnable> getRunnables() {
		return runnables;
	}
	
	/**
	 * Add a runnable to the task execution.
	 * @param _runnable Runnable to be executed by the task.
	 */
	public void addRunnable(QnxRunnable _runnable) {
		if (!runnables.contains(_runnable)) {
			runnables.add(_runnable);
			_runnable.addTask(this);
		}
	}
	
	/**
	 * Set a deadline to a task.
	 * @param deadline_ms Deadline value in ms.
	 */
	public void setDeadline_ms(long deadline_ms) {
		this.deadline_ms = deadline_ms;
	}
	
	/**
	 * Get the task deadline in ms.
	 * @return deadline value in ms.
	 */
	public long getDeadline_ms() {
		return deadline_ms;
	}
	
	@Override
	public String toString() {
		String output = name + " T = " + period_ms + "[ms]\n";
		
		for (QnxRunnable r : runnables) {
			output += "\t" + r.getName() + "\n";
		}
		
		return output;
	}

	/**
	 * Set the task priority. Larger values denote a higher priority.
	 * Min priority = 1
	 * Max priority = 255
	 * @param _priority Task priority.
	 */
	public void setPriority(int _priority) {
		if (priority != -1) {
			System.err.println("Priority of task " + name + " can only be set once! Double allocation not allowed.");
			System.exit(1);
		}
		
		if (_priority > 0 && _priority <= 255) {
			priority = _priority;
		} else {
			System.err.println("Priority of task " + name + " out of range! (Must be between 1 and 255.)");
			System.exit(1);
		}
	}
	
	/**
	 * Get the list of labels with read access of all runnables assigned to the task.
	 * @return List of labels with read access.
	 */
	public ArrayList<QnxLabel> getAllReadLabels() {
		ArrayList<QnxLabel> labels = new ArrayList<QnxLabel>();
		
		for (QnxRunnable runnable : runnables) {
			for (QnxLabel label : runnable.getReadLabels()) {
				if (!labels.contains(label)) labels.add(label);
			}
		}
		
		return labels;
	}
	
	/**
	 * Get the list of labels with write access of all runnables assigned to the task.
	 * @return List of labels with write access.
	 */
	public ArrayList<QnxLabel> getAllWriteLabels() {
		ArrayList<QnxLabel> labels = new ArrayList<QnxLabel>();
		
		for (QnxRunnable runnable : runnables) {
			for (QnxLabel label : runnable.getWriteLabels()) {
				if (!labels.contains(label)) labels.add(label);
			}
		}
		
		return labels;
	}
	
	/**
	 * Add a new channel to the set of channels the task sends write labels to (on other nodes).
	 * @param _channel Communication channel to receive write labels on other nodes.
	 */
	public void addSenderChannel(QnxComChannel _channel) {
		if (!senderChannels.contains(_channel)) {
			senderChannels.add(_channel);
		}
	}

	/**
	 * Set the criticality value for the task. Smaller values indicate a larger criticality.
	 * @param _criticality Criticality of the task as integer.
	 */
	public void setCriticality(int _criticality) {
		criticality = _criticality;
	}

	/**
	 * Returns the criticality of the task. Smaller values indicate a larger criticality.
	 * @return Criticality of the task.
	 */
	public int getCriticality() {
		return criticality;
	}
}
