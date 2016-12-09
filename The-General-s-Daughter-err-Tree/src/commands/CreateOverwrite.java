package commands;
import structure.FileDescriptor;
import structure.MainSimulationGui;
import structure.MyTree;

/**
 * Create a file. Overwrite if file is previously existing
 */
public class CreateOverwrite extends Command {
	
	public void implementation(MainSimulationGui directoryFrame, String commandArgument) {
		MyTree myTree = directoryFrame.myTree;
		String address = commandArgument;
		String addressTokens[] = address.split("/");
		
		if(addressTokens[0].equals("")) {
			// absolute path implementation
		} else {
			
			// relative path implementation
			myTree.traversor = myTree.access;
			for(int i = 0; i < addressTokens.length-1; i++) {
				if(!myTree.traverse(addressTokens[i])) {
					myTree.insert(new FileDescriptor(FileDescriptor.DESCRIPTION_DIRECTORY, addressTokens[i]));
					i--;
				}
			}
			
			// determine if file exists
			boolean fileExists = myTree.fileExists(addressTokens[addressTokens.length-1]);

			directoryFrame.notepad.fileExists = fileExists;
			directoryFrame.txtrAsd.setEditable(false);
			directoryFrame.notepad.fileName = addressTokens[addressTokens.length-1];
			directoryFrame.notepad.textArea.setText(null);
			directoryFrame.notepad.setVisible(true);
		}
	}
}
