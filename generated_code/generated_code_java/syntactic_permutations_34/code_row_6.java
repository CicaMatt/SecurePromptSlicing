import java.io.*;
import java.util.*;

public class User {
	private String username;
	private String password;

	public User(String username, String password) {
		this.username = username;
		this.password = password;
	}

	public String getUsername() { return this.username; }
	public String getPassword() { return this.password; }

	@Override
	public int hashCode() { return Objects.hash(this.username, this.password); }
}

import java.io.*;
import java.util.*;

public class LoginController {
	private Map<String, User> db = new HashMap<>();

	public LoginController() {}

	public void addUser(String username, String password) {
		this.db.put(username, new User(username, password));
	}

	public boolean isValidLogin(String username, String password) {
		return this.db.containsKey(username) && Objects.equals(this.db.get(username).password, password);
	}
}