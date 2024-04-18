package mabecker.qnx.codegeneration.model;

import java.util.ArrayList;

public class QnxComChannel {

	private String 				name;		// Name of the channel
	private QnxTask 			sender;		// Sender task
	private QnxTask 			receiver;	// Receiver task 
	private ArrayList<QnxLabel> labels;		// List of labels sent over this channel
	
	public QnxComChannel(String _name) {
		name = _name;
		sender = null;
		receiver = null;
		labels = new ArrayList<QnxLabel>();
	}
	
	/**
	 * Get the name of the channel.
	 * @return Name string.
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * Get the receiver task of the channel.
	 * @return Receiver task.
	 */
	public QnxTask getReceiver() {
		return receiver;
	}
	
	/**
	 * Get the sender task of the channel.
	 * @return List of all sender nodes.
	 */
	public QnxTask getSender() {
		return sender;
	}
	
	/**
	 * Set the receiver task of the channel.
	 * @param receiver Receiver task.
	 */
	public void setReceiver(QnxTask _receiver) {
		this.receiver = _receiver;
	}
	
	/**
	 * Add a new sender node to the system.
	 * @param _node Sender node.
	 */
	public void setSender(QnxTask _task) {
		sender = _task;
		_task.addSenderChannel(this);
	}
	
	/**
	 * Get the list of all labels sent over this channel.
	 * @return List of QnxLabels.
	 */
	public ArrayList<QnxLabel> getLabels() {
		return labels;
	}
	
	/**
	 * Add a new label to this channel. 
	 * If the label already is in the list it is  not added again.
	 * @param _label Label to be added to the channel.
	 */
	public void addLabel(QnxLabel _label) {
		if (!labels.contains(_label)) {
			labels.add(_label);
		}
	}
	
	/**
	 * Returns the size of all labels in bytes.
	 * @return Size of channel labels in byte.
	 */
	public long getPayloadSizeByte() {
		long size = 0;
		
		for (QnxLabel label : labels) {
			size += label.getSize_byte();
		}
		
		return size;
	}
}
