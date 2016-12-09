package commands;
import structure.FileDescriptor;
import structure.MainSimulationGui;
import structure.MyTree;

/**
 * Remove directory
 */
public class Rmdir extends Command {
	
	public void implementation(MainSimulationGui directoryFrame, String commandArgument) {
		MyTree myTree = directoryFrame.myTree;
		String address = commandArgument;
		String addressTokens[] = address.split("/");
		
		if(addressTokens[0].equals("")) {
			
			// absolute path implementation
		} else {
			
			// relative path implementation
			boolean pathfind = true;
			myTree.traversor = myTree.access;
			for(int i = 0; i < addressTokens.length; i++) {
				if(!myTree.traverse(addressTokens[i]) || myTree.traversor.fileDescriptor.description.equals(FileDescriptor.DESCRIPTION_FILE)) {
					directoryFrame.txtrAsd.append("The system cannot find the path specified.\n");
					pathfind = false;
					break;
				}
			}
			
			if(pathfind) { 
				
				if(myTree.traversor.children.size() != 0) {
					
					// if directory is empty
					directoryFrame.txtrAsd.append("The directory is not empty.\n");
				} else {
					myTree.remove();
				}
			}
		}
	}
}
