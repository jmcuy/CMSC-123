package commands;
import structure.MainSimulationGui;

public class Error extends Command {
	private String errorMessage;
	
	public Error() {
		errorMessage = " is not recognized as an internal or external command, \noperable program or batch file.";
	}
	
	public void implementation(MainSimulationGui directoryFrame, String command) {		
		directoryFrame.txtrAsd.append("'"+ command + "'" + errorMessage + "\n");
	}
}
