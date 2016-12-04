
public class Rmdir extends Command {
	
	public Rmdir() {
		
	}
	
	public void implementation() {
		if(addressTokens[0].equals("")) {
			// absolute path implementation
		} else {
			// relative path implementation
			boolean pathfind = true;
			myTree.traversor = myTree.access;
			for(int i = 0; i < addressTokens.length; i++) {
				if(!myTree.traverse(addressTokens[i])) {
					System.out.println("The system cannot find the path specified");
					pathfind = false;
					break;
				}
			}
			if(pathfind) {
				myTree.remove();
			}
		}
	}
}
