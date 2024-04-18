package mabecker.qnx.codegeneration.model;

public class Core {

	private QnxNode node;	// QNX node the core belongs to
	private int 	id;		// Core ID (starting from 0)
	private String 	name;	// Name of the core
	
	/**
	 * Create a new core
	 * @param _id	ID of the core (starting from 0).
	 */
	public Core(String _name, int _id) {
		node = null;
		name = _name;
		id = _id;
	}
	
	/**
	 * Return the name of the core.
	 * @return Name string.
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * Add the QNX node the core belongs to.
	 * @param _node QNX node.
	 */
	public void addNode(QnxNode _node) {
		node = _node;
	}
	
	/**
	 * Get the ID of the core.
	 * @return Core ID.
	 */
	public int getId() {
		return id;
	}
	
	/**
	 * Get the node the core belongs to.
	 * @return QNX node.
	 */
	public QnxNode getNode() {
		return node;
	}
	
	@Override
	public String toString() {
		return "Core-id:" + id + " name: " + name;
	}
}
