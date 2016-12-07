
public class Mkdir extends Command {

	public Mkdir() {

	}
	
	public void implementation(MyTree myTree, String address) {
		String addressTokens[] = address.split("/");
		
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
