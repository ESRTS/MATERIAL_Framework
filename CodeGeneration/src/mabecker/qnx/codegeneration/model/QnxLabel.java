package mabecker.qnx.codegeneration.model;

import java.util.ArrayList;

public class QnxLabel {
	
	private String 					name;		// Name of the label
	private long 					size_byte;	// Size of the label in bytes
	private ArrayList<QnxRunnable> 	readers;	// List of all runnables that read the label
	private ArrayList<QnxRunnable> 	writers;	// List of all runnables that write to the label
	
	/**
	 * Create a new data label.
	 * @param _name	Name of the label.
	 * @param _size_byte Size of the label in bytes.
	 */
	public QnxLabel(String _name, long _size_byte) {
		name = _name;
		size_byte = _size_byte;
		readers = new ArrayList<QnxRunnable>();
		writers = new ArrayList<QnxRunnable>();
	}
	
	/**
	 * Return the name of the runnable.
	 * @return Name string.
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * Return the size of the runnable in bytes.
	 * @return Size in bytes.
	 */
	public long getSize_byte() {
		return size_byte;
	}
	
	/**
	 * Add a new runnable to the list of readers
	 * @param reader Reading runnable.
	 */
	public void registerReader(QnxRunnable reader) {
		if (!readers.contains(reader)) {	
			readers.add(reader);
		}
	}
	
	/**
	 * Add a new runnable to the list of writers
	 * @param writer Writing runnable.
	 */
	public void registerWriter(QnxRunnable writer) {
		if (!writers.contains(writer)) {
			writers.add(writer);
		}
	}
	
	@Override
	public String toString() {
		return name + " -> " + size_byte + "[b]";
	}
}
