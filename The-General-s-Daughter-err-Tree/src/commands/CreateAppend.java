package commands;
import structure.FileDescriptor;
import structure.MainSimulationGui;
import structure.MyNode;
import structure.MyTree;

/**
 * Create a file. Append if file is previously existing
 */
public class CreateAppend extends Command {
	
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
			
			if(fileExists) {
				MyNode file = myTree.getFile(addressTokens[addressTokens.length-1]);
				directoryFrame.notepad.file = file;
				directoryFrame.notepad.textArea.setText(file.fileDescriptor.contents);
			} else {
				directoryFrame.notepad.textArea.setText(null);
			}
			
			directoryFrame.notepad.setVisible(true);
		}
	}
}
