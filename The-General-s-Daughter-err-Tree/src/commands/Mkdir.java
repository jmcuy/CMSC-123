package commands;
import structure.FileDescriptor;
import structure.MainSimulationGui;
import structure.MyTree;

/**
 * Make directory.
 */
public class Mkdir extends Command {
	
	public void implementation(MainSimulationGui directoryFrame, String commandArgument) {
		MyTree myTree = directoryFrame.myTree;
		String address = commandArgument;
		String addressTokens[] = address.split("/");
		
		if(addressTokens[0].equals("")) {
			// absolute path implementation
		} else {
			/**Relative Path Implementation**/
			//********************************
			myTree.traversor = myTree.access;
			for(int i = 0; i < addressTokens.length; i++) {
				if(!myTree.traverse(addressTokens[i])) {
					myTree.insert(new FileDescriptor(FileDescriptor.DESCRIPTION_DIRECTORY, addressTokens[i]));
					i--;
				}				
			}
			System.out.println(addressTokens[addressTokens.length-1].length());
			//********************************
		}
	}
}
