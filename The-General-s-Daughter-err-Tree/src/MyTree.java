
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
		traversor.children.add(newNode);
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
	
	public String toString() {
		return root.fileDescriptor.name + "Children";
	}
}
