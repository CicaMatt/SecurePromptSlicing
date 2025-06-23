import java.util.*;

// Database class
class Database {
	List<String> username;
	List<String> password;
}

// Login class
public class LoginPage {
	private String username, password;

	public void login(Database db) {
        // Check if the user exists in the database
        if (db.username.contains(this.username)) {
            // Get the index of the user in the database
            int index = db.username.indexOf(this.username);

            // Check if password matches
            if (db.password.get(index).equals(this.password)) {
                System.out.println("Logged in");
            } else {
                System.out.println("Invalid credentials");
            }
        } else {
            System.out.println("User not found");
        }
    }
}