package mabecker.qnx.codegeneration.model;

import java.util.ArrayList;

public class EdgeSystem {

	private String						model;		// Path to the original Amalthea model
	private String 						name;		// Name of the application
	private ArrayList<QnxNode> 			nodes;		// All QNX nodes of the system
	private ArrayList<QnxLabel> 		labels;		// All QNX labels of the system
	private ArrayList<QnxRunnable>  	runnables; 	// All QNX runnables of the system
	private ArrayList<QnxTask>			tasks;		// All QNX tasks of the system
	private ArrayList<QnxComChannel>	channels;	// All QNX communication channels
	
	public EdgeSystem(String _name, String _model) {
		model = _model;
		name = _name;
		nodes = new ArrayList<QnxNode>();
		labels = new ArrayList<QnxLabel>();
		runnables = new ArrayList<QnxRunnable>();
		tasks = new ArrayList<QnxTask>();
		channels = new ArrayList<QnxComChannel>();
	}
	
	public String getName() {
		return name;
	}
	
	/**
	 * Returns the path to the original Amalthea model.
	 * @return Madel path string.
	 */
	public String getModelPath() {
		return model;
	}
	
	/**
	 * Get the list of all nodes.
	 * @return List of all nodes.
	 */
	public ArrayList<QnxNode> getNodes() {
		return nodes;
	}
	
	/**
	 * Add a node to the system.
	 * @param _node New node to add.
	 */
	public void addNode(QnxNode _node) {
		if (!nodes.contains(_node)) {
			nodes.add(_node);
			_node.addSystem(this);
		}
	}
	
	/**
	 * Get all labels that exist in the system.
	 * @return List of all labels.
	 */
	public ArrayList<QnxLabel> getLabels() {
		return labels;
	}
	
	/**
	 * Get all runnables that exist in the system.
	 * @return List of all runnables.
	 */
	public ArrayList<QnxRunnable> getRunnables() {
		return runnables;
	}
	
	/**
	 * Get all tasks that exist in the system.
	 * @return List of all tasks.
	 */
	public ArrayList<QnxTask> getTasks() {
		return tasks;
	}
	
	/**
	 * Add a new label to the set of labels.
	 * @param _label Add new label.
	 */
	public void addLabel(QnxLabel _label) {
		if (!labels.contains(_label)) {
			labels.add(_label);
		}
	}
	
	/**
	 * Add a new task to the system.
	 * @param _task Add new task.
	 */
	public void addTask(QnxTask _task) {
		if (!tasks.contains(_task)) {
			tasks.add(_task);
		}
	}
	
	/**
	 * Add a new runnable to the system.
	 * @param _runnable Add new runnable.
	 */
	public void addRunnable(QnxRunnable _runnable) {
		if (!runnables.contains(_runnable)) {
			runnables.add(_runnable);
		}
	}
	
	@Override
	public String toString() {
		
		String[] parts = model.split("[/.]");
		String  name = parts[parts.length - 2];
		String output = "System: " + name;
		
		return output;
	}

	/**
	 * Helper method to return the QnxTask of a given name.
	 * @param name Name of the QNX task.
	 * @return QnxTask instance of the given name. If the task does not exist, return null.
	 */
	public QnxTask findTaskByName(String _name) {
		
		for (QnxTask t : tasks) {
			if (t.getName().equals(_name)) return t;
		}
		return null;
	}
	
	/**
	 * Returns all communication channels.
	 * @return List of communication channels.
	 */
	public ArrayList<QnxComChannel> getChannels() {
		return channels;
	}
	
	/**
	 * Add a new communication channel to the system.
	 * @param _channel New communication channel to be added.
	 */
	public void addChannel(QnxComChannel _channel) {
		if (!channels.contains(_channel)) {
			channels.add(_channel);
		}
 	}

	/**
	 * Returns a larger description of the complete system
	 * @return System description string
	 */
	public String print() {
		String output = "System: " + name + "\n";
		
		for (QnxNode node : nodes) {
			output += node.print();
		}
		
		return output;
	}
}
