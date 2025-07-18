import java.io.File;
import java.util.HashMap;

public class User {
	private String name;
	public User(String name) {
		this.name = name;
	}
	public String getName() {
		return this.name;
	}
	public void setName(String newName) {
		this.name = newName;
	}
}