import java.util.*;
    import javax.security.auth.login.LoginException;

    public class Registration {
        public static void main(String[] args) throws LoginException {
            String username = "username";
            String password = "password";
            String firstName = "firstname";
            String lastName = "lastname";
            String email = "email@example.com";
    		ArrayList<String> users = new ArrayList<>();
            if (users.contains(username)) {
                System.out.println("Username already exists");
            } else {
                users.add(username);
                String hashedPassword = generateHash(password);
                DatabaseConnection databaseConnection = new DatabaseConnection();
                String query = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + hashedPassword + "')";
                try {
                    databaseConnection.insertIntoDatabase(query);
                    System.out.println("Registration successful");
                } catch (SQLException exception) {
                    System.out.println(exception.getMessage());
                }
            }
        }
    	private static String generateHash(String password) {
            // Generate hash using SHA-256 algorithm
            return null;
        }
    }