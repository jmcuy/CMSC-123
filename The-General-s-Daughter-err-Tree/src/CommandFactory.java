
public class CommandFactory {
	
	public static Command makeCommand(String commandName) {
		Command command;
		
		switch(commandName) {
		case "mkdir" : 
			command = new Mkdir();
			break;
		case "rmdir" :
			command = new Rmdir();
			break;
		default : 
			command = new Error();
			break;
		}
		
		return command;
	}

}
