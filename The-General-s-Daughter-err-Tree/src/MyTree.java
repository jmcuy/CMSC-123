
public class MyTree {
	MyNode root;
	MyNode access;
	MyNode traversor;
	
	public MyTree() {
		root = new MyNode(new FileDescriptor("director", "root"));
		access = root;
	}
	
	public void insert(FileDescriptor fileDescriptor) {
		MyNode newNode = new MyNode(fileDescriptor);
		newNode.parent = traversor;
		//traversor.children.add(newNode);
		
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
		for(MyNode childNode : traversor.children) {
			if(childNode.fileDescriptor.name.equals(address)) {
				traversor = childNode;
				break;
			}
		}
		return currentNode != traversor;
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
	
	public String toString() {
		int level = 0;
		return root.toString(level);
	}
}
