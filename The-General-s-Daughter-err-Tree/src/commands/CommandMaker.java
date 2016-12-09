package commands;
import structure.MainSimulationGui;

public class CommandMaker {
	Command mkdir = new Mkdir();
	Command rmdir = new Rmdir();
	Command cd = new Cd();
	Command createOverwrite = new CreateOverwrite();
	Command createAppend = new CreateAppend();
	Command error = new Error();
	
	public void implementation(MainSimulationGui directoryFrame, String command, String commandArgument) {
		switch(command) {
		case "mkdir" : 
			mkdir.implementation(directoryFrame, commandArgument);
			break;
		case "rmdir" :
			rmdir.implementation(directoryFrame, commandArgument);
			break;
		case "cd" :
			cd.implementation(directoryFrame, commandArgument);
			break;
		case ">" :
			createOverwrite.implementation(directoryFrame, commandArgument);
			break;
		case ">>" :
			createAppend.implementation(directoryFrame, commandArgument);
			break;
		default : 
			error.implementation(directoryFrame, command);
			break;
		}
	}
}
