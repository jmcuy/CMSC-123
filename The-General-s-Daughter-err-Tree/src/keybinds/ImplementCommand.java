package keybinds;
import java.awt.event.ActionEvent;

import structure.MainSimulationGui;

/**
 * Action to bind to text area when "Enter" key is pressed 
 * When enter key is pressed, text area takes user input
 * and performs the command given from the user input.
 */
public class ImplementCommand extends KeyBind {
	private static final String KEY = "ENTER";

	public ImplementCommand(MainSimulationGui directoryFrame) {
		super(directoryFrame, KEY);
	}

	@Override
	public void actionPerformed(ActionEvent e) {    	
    	String screen = directoryFrame.txtrAsd.getText();
    	String input = screen.substring(directoryFrame.startIndex);
    	String inputTokens[] = input.split(" ", 2);
    	String commandName;
		String commandArgument;
		
		// continue to append new line
    	directoryFrame.txtrAsd.append("\n");
		
		/**Handle Command**/
		//******************
		
		// set commandName to the first word of the user input in the text area
		commandName = inputTokens[0];
		if(inputTokens.length >= 2) {
			
			// handles more than one word input in text area
			commandArgument = inputTokens[1];
		} else {
			
			// handles one word input in text area
			commandArgument = "";
		}
		
		// performs the implementation given the command(first word of the input)
		// and the auxiliary command(the whole string after the first word)
		directoryFrame.fileSystem.implementation(commandName, commandArgument);
		//******************
		
		// after implementation of the command the current directory of the file system is displayed
		directoryFrame.txtrAsd.append(directoryFrame.myTree.currentAbsolutePath() + ">");
		
		// update startIndex
		directoryFrame.startIndex = directoryFrame.txtrAsd.getText().length(); 
		
		// print to console the structure of the file system
		System.out.println(directoryFrame.myTree);
		
	}
}
