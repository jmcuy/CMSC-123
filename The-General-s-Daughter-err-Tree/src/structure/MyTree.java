package structure;

/**
 * Core structure of the file system
 */
public class MyTree {
	public MyNode root;
	public MyNode access;
	public MyNode traversor;
	
	public MyTree() {
		root = new MyNode(new FileDescriptor("directory", "root"));
		access = root;
	}
	
	public void insert(FileDescriptor fileDescriptor) {
		MyNode newNode = new MyNode(fileDescriptor);
		newNode.parent = traversor;
		
		int i = 0;
		for(; i < traversor.children.size(); i++) {
			MyNode childNode = traversor.children.get(i);
			if(newNode.fileDescriptor.name.compareTo(childNode.fileDescriptor.name) < 0) {
				break;
			}
		}
		traversor.children.add(i, newNode);
	}
	
	public void remove() {
		MyNode nodeDel = traversor;
		MyNode nodeDelParent = traversor.parent;
		nodeDel.parent = null;
		nodeDelParent.children.remove(nodeDel);
	}
	
	public boolean traverse(String address) {
		MyNode currentNode = traversor;
		
		if(address.equals("..")) {
			
			// traverse to parent
			traversor = traversor.parent;
			
		} else {
			for(MyNode childNode : traversor.children) {
				if(childNode.fileDescriptor.name.equals(address) && childNode.fileDescriptor.description.equals(FileDescriptor.DESCRIPTION_DIRECTORY)) {
					traversor = childNode;
					break;
				}
			}
		}

		return currentNode != traversor;
	}
	
	public boolean fileExists(String fileName) {
		for(MyNode childNode : traversor.children) {
			if(childNode.fileDescriptor.name.equals(fileName) && childNode.fileDescriptor.description.equals(FileDescriptor.DESCRIPTION_FILE)) {
				return true;
			}
		}
		return false;
	}
	
	public String currentAbsolutePath() {
		String stringResult = "";
		MyNode node = access;
		stringResult += absolutePathRecur(node);
		return stringResult;
	}
	
	private String absolutePathRecur(MyNode node) {
		if(node.parent == null) {
			return node.fileDescriptor.name;
		} else {
			return absolutePathRecur(node.parent) + "/" + node.fileDescriptor.name;	
		}
		
	}
	
	public MyNode getFile(String fileName) {
		for(MyNode childNode : traversor.children) {
			if(childNode.fileDescriptor.name.equals(fileName) && childNode.fileDescriptor.description.equals(FileDescriptor.DESCRIPTION_FILE)) {
				return childNode;
			}
		}
		return null;
	}
	
	public String toString() {
		int level = 0;
		return root.toString(level);
	}
}
