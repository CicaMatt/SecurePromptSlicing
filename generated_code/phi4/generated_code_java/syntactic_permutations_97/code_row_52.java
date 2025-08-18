import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.mindrot.jbcrypt.BCrypt;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        registerUser("newuser", "securePassword123", "John", "Doe", "john.doe@example.com");
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Check if the username already exists
            PreparedStatement checkStmt = conn.prepareStatement("SELECT 1 FROM users WHERE username = ?");
            checkStmt.setString(1, username);
            ResultSet rs = checkStmt.executeQuery();

            if (rs.next()) {
                System.out.println("Username already exists.");
                return;
            }

            // Hash the password
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            // Insert new user into database
            PreparedStatement insertStmt = conn.prepareStatement(
                    "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)");
            insertStmt.setString(1, username);
            insertStmt.setString(2, hashedPassword);
            insertStmt.setString(3, firstName);
            insertStmt.setString(4, lastName);
            insertStmt.setString(5, email);

            int rowsAffected = insertStmt.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("User registered successfully.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


**Note**: Before running this code, ensure you have:
- MySQL JDBC Driver in your classpath.
- A database named `your_database` with a table `users` having columns: `username`, `password`, `first_name`, `last_name`, and `email`.
- Replace the `DB_URL`, `USER`, and `PASS` values with your actual database credentials.