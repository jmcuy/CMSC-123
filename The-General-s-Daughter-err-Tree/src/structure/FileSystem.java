package structure;
import commands.CommandMaker;

/**
 * Contains the core structure and commands of the virtual directory
 */
public class FileSystem {
	MainSimulationGui directoryFrame;
	CommandMaker commandMaker;
	
	public FileSystem(MainSimulationGui directoryFrame) {
		this.directoryFrame = directoryFrame;
		commandMaker = new CommandMaker();
	}
	
	public void implementation(String command, String commandArgument) {
		commandMaker.implementation(directoryFrame, command, commandArgument);
	}
	
	public String showTree() {
		return directoryFrame.myTree.toString();
	}
}
