
public class Mkdir extends Command {

	public Mkdir() {

	}
	
	public void implementation() {
		if(addressTokens[0].equals("")) {
			// absolute path implementation
		} else {
			// relative path implementation
			myTree.traversor = myTree.access;
			for(int i = 0; i < addressTokens.length; i++) {
				if(!myTree.traverse(addressTokens[i])) {
					myTree.insert(new FileDescriptor("directory", addressTokens[i]));
					i--;
				}
			}
		}
	}
}
