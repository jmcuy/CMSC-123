package keybinds;
import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;

import structure.MainSimulationGui;

/**
 * Actions to bind to text area
 */
public abstract class KeyBind extends AbstractAction {
	MainSimulationGui directoryFrame;
	private String key;
	
	public KeyBind(MainSimulationGui directoryFrame, String key) {
		this.directoryFrame = directoryFrame;
		this.key = key;
	}

	@Override
	public abstract void actionPerformed(ActionEvent e);
	
	public String getKey() {
		return key;
	}

}
