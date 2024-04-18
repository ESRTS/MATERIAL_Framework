package mabecker.qnx.codegeneration.model;

public class QnxMode {

	private int 		condition;		// Value of the mode variable to trigger this mode
	private long 		executionTicks;	// Execution time of this mode in ticks
	private QnxRunnable runnable;		// Runnable the mode belongs to
	/**
	 * Create a new mode.
	 * @param _condition Value of the mode variable to trigger this mode.
	 * @param _executionTime Execution time when in this mode.
	 * @param _runnable Runnable the mode is assigned to.
	 */
	public QnxMode(int _condition, long _executionTime, QnxRunnable _runnable) {
		condition = _condition;
		runnable = _runnable;
		executionTicks = _executionTime;
	}
	
	/**
	 * Get the execution time of the mode.
	 * @return Mode execution time.
	 */
	public long getExecutionTicks() {
		return executionTicks;
	}
	
	/**
	 * Get the value of the mode variable that triggers this mode.
	 * @return Mode variable value.
	 */
	public int getCondition() {
		return condition;
	}
	
	/**
	 * Get the runnable the mode belongs to.
	 * @return Runnable of the mode.
	 */
	public QnxRunnable getRunnable() {
		return runnable;
	}
}
