package mabecker.qnx.codegeneration.model;

import java.util.ArrayList;

public class ApsPartition {

	private ArrayList<QnxTask> 	tasks;					// List of tasks assigned to this APS partition
	private int 				budgetPercentageScale;	// The number of digits to the right of the decimal point in budgetPercent 
	private int 				budgetPercent;			// Budget value expressed as percentage
	private QnxNode 			node;					// The QNX node this partition belongs to
	private boolean 			isSystemPartition;		// A flag indicating if this is the system partition
	private String 				name;					// Name of the partition
	
	/**
	 * Create a new APS partition with a given budget.
	 * @param _budgetPercent
	 * @param _budgetPercentageScale
	 */
	public ApsPartition(String _name, int _budgetPercent, int _budgetPercentageScale, boolean _isSystemPartition) {
		name = _name;
		tasks = new ArrayList<QnxTask>();
		budgetPercent = _budgetPercent;
		budgetPercentageScale = _budgetPercentageScale;
		node = null;
		isSystemPartition = _isSystemPartition;
	}
	
	/**
	 * Get the name of the APS partition.
	 * @return Partition name.
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * Get the parameter budget percentage for the partition. This describes the percentage on system level (system utilization is 100%)
	 * @return 
	 */
	public int getBudgetPercent() {
		return budgetPercent;
	}
	
	/**
	 * Set a new budget percent value for this partition.
	 * @param budgetPercent Get the current budget percent value.
	 */
	public void setBudgetPercent(int budgetPercent) {
		this.budgetPercent = budgetPercent;
	}
	
	/**
	 * Get the budget percentage scale factor.
	 * @return The number of digits to the right of the decimal point in budgetPercent 
	 */
	public int getBudgetPercentageScale() {
		return budgetPercentageScale;
	}
	
	/**
	 * Set a new value for the Budget Percentage Scale factor.
	 * @param budgetPercentageScale new scale factor.
	 */
	public void setBudgetPercentageScale(int budgetPercentageScale) {
		this.budgetPercentageScale = budgetPercentageScale;
	}
	
	/**
	 * Get the QNX node the partition belongs to.
	 * @return QNX node of the partition.
	 */
	public QnxNode getNode() {
		return node;
	}
	
	/**
	 * Get the list of tasks assigned to the partition.
	 * @return Task list.
	 */
	public ArrayList<QnxTask> getTasks() {
		return tasks;
	}
	
	/**
	 * Add a new task to the APS partition. 
	 * @param _task New task to add to the partition.
	 */
	public void addTask(QnxTask _task) {
		if (!tasks.contains(_task)) {
			tasks.add(_task);
			_task.setPartition(this);
		}
	}
	
	/**
	 * Method to check if this partition is the system partition.
	 * @return True if it is the system partition and false otherwise.
	 */
	public boolean isSystemPartition() {
		return isSystemPartition;
	}

	/**
	 * Register to which QNX node the partition belongs to.
	 * @param _node QNX node.
	 */
	public void addNode(QnxNode _node) {
		node = _node;
	}
	
	@Override
	public String toString() {
		return name + " " + getBudgetString() + " [" + budgetPercent + ", " + budgetPercentageScale + "]";
	}

	/**
	 * Generate the percentage value of the budget based on budgetPercent and budgetPercentageScale.
	 * Note that this value is global, so it applies to all CPUs in the system.
	 * @return Budget string in percent
	 */
	private String getBudgetString() {
		
		int tmp = budgetPercentageScale;
		int divider = 1;
		while (tmp > 0) {
			divider = divider * 10;
			tmp--;
		}
		
		int fractionPart = budgetPercent % divider;
		int integerPart = (budgetPercent - fractionPart) / divider;
				
		return integerPart + "." + fractionPart + "%";
	}
}
