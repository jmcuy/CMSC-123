
public class Cd extends Command {
	
	public Cd() {
		
	}
	
	public void implementation(MyTree myTree, String address) {
		String addressTokens[] = address.split("/");
		
		if(addressTokens[0].equals("")) {
			// absolute path implementation
		} else {
			// relative path implementation
			if(addressTokens[0].equals("..")) {
				if(myTree.access != myTree.root) {
					myTree.access = myTree.access.parent;
				}
			} else {
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
					myTree.access = myTree.traversor;
				}
			}

		}
	}

}
