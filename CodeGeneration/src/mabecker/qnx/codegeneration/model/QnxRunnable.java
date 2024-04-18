package mabecker.qnx.codegeneration.model;

import java.util.ArrayList;

public class QnxRunnable {
	
	private String 				name;			// Name of the runnable
	private ArrayList<QnxLabel> readLabels;		// List of labels with read access	
	private ArrayList<QnxLabel> writeLabels;	// List of labels with write access
	private ArrayList<QnxTask>	tasks;			// Task the runnable is assigned to
	private ArrayList<QnxMode>	modes;			// List of execution modes
	private QnxRunnableType		type;			// Runnable type
	private int					criticality;	// Criticality of the task,  smaller values indicate a larger criticality
	private QnxComChannel		channel;		// Channel in case it is a communication runnable
	
	/**
	 * Create a new runnable
	 * @param _name Unique name of the runnable.
	 * @param _type Runnable type. This can only be set during creation.
	 */
	public QnxRunnable(String _name, QnxRunnableType _type) {
		name = _name;
		tasks = new ArrayList<QnxTask>();
		readLabels = new ArrayList<QnxLabel>();
		writeLabels = new ArrayList<QnxLabel>();
		modes = new ArrayList<QnxMode>();
		type = _type;
		channel = null;
		criticality = 0;	// critical if not specified different later on
	}
	
	/**
	 * Return the tasks the runnable is assigned to. 
	 * @return Tasks to execute the runnable.
	 */
	public ArrayList<QnxTask> getTasks() {
		return tasks;
	}
	
	/**
	 * Return the unique runnable name.
	 * @return Name string.
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * Return the list of labels the runnable reads.
	 * @return Labels with read access.
	 */
	public ArrayList<QnxLabel> getReadLabels() {
		return readLabels;
	}
	
	/**
	 * Return the list of labels the runnable writes.
	 * @return Labels with write access.
	 */
	public ArrayList<QnxLabel> getWriteLabels() {
		return writeLabels;
	}
	
	/**
	 * Add a new label the runnable reads.
	 * @param _label Label with read access.
	 */
	public void addLabelRead(QnxLabel _label) {
		
		if (type == QnxRunnableType.RECEIVER_RUNNABLE) {
			System.err.println("Cannot add read label to runnable of type RECEIVER_RUNNABLE");
			System.exit(1);
		}
		
		if (!readLabels.contains(_label)) {
			readLabels.add(_label);
			_label.registerReader(this);
		}
	}
	
	/**
	 * Add a new label the runnable writes.
	 * @param _label Label with write access.
	 */
	public void addLabelWrite(QnxLabel _label) {
		
		if (type == QnxRunnableType.SENDER_RUNNABLE) {
			System.err.println("Cannot add read label to runnable of type SENDER_RUNNABLE");
			System.exit(1);
		}
		
		if (!writeLabels.contains(_label)) {
			writeLabels.add(_label);
			_label.registerWriter(this);
		}
	}
	
	/**
	 * Add a task to execute the runnable. Note that the runnable can be part of multiple tasks. 
	 * However, all execution follows the same global runnable mode.
	 * @param _task Task the runnable is assigned to
	 */
	public void addTask(QnxTask _task) {
		if (!tasks.contains(_task)) {
			tasks.add(_task);
		}
	}
	
	/**
	 * Add a new mode to the runnable
	 * @param _mode
	 * @return False if the mode condition is already used, true otherwise.
	 */
	public boolean addMode(int _condition, long _executionTicks) {
		
		if (type != QnxRunnableType.USER_RUNNABLE) {
			System.err.println("Can only add a mode to runnables of type USER_RUNNABLE");
			System.exit(1);
		}
		
		for (QnxMode mode : modes) {
			if (mode.getCondition() == _condition) {
				return false;	// Each condition can only appear once.
			}
		}
		
		QnxMode mode = new QnxMode(_condition, _executionTicks, this);
		modes.add(mode);
		
		return true;
	}
	
	@Override
	public String toString() {
		String output = "Runnable: " + name;
		
		return output;
	}
	
	/**
	 * Returns the modes of the runnable.
	 * @return List of modes.
	 */
	public ArrayList<QnxMode> getModes() {
		return modes;
	}
	
	/**
	 * Returns the execution time of the runnable in us. This depends on the runnable to task, 
	 * task to node allocation and the execution mode.
	 * @return
	 */
	public long getExecTime_us(int _modeIndex, QnxNode _node) {
		
		long tps = _node.getTicksPerSecond();
		long exec = modes.get(_modeIndex).getExecutionTicks();
		
		double execTime_us = ((double)exec / (double)tps) * 1000000;	// Get the execution time in us
		
		return Math.round(execTime_us);
	}
	
	/**
	 * Get the runnable type.
	 * @return Runnable type.
	 */
	public QnxRunnableType getType() {
		return type;
	}
	
	/**
	 * Set the communication channel of the runnable.
	 * @param channel Communication channel.
	 */
	public void setChannel(QnxComChannel channel) {
		this.channel = channel;
	}
	
	/**
	 * Get the communication channel of the runnable in case it is a com runnable.
	 * @return Communication channel.
	 */
	public QnxComChannel getChannel() {
		return channel;
	}
	
	/**
	 * Method returns the base mode of the task. This is either the first registered mode
	 * or mode 0 if there is no mode registered. 
	 * @return Base more of the task.
	 */
	public int getBaseMode() {
		if (modes.size() > 0) {
			return modes.get(0).getCondition();
		}
		return 0;
	}
	
	/**
	 * Set the criticality value for the runnable. Smaller values indicate a larger criticality.
	 * @param _criticality Criticality of the runnable as integer.
	 */
	public void setCriticality(int _criticality) {
		criticality = _criticality;
	}

	/**
	 * Returns the criticality of the runnable. Smaller values indicate a larger criticality.
	 * @return Criticality of the runnable.
	 */
	public int getCriticality() {
		return criticality;
	}
}
