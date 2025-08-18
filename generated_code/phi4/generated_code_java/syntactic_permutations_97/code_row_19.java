import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.mindrot.jbcrypt.BCrypt;

public class Registration {

    private static final String URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        try {
            registerUser("testUsername", "password123", "FirstName", "LastName", "email@example.com");
        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }

    public static String registerUser(String username, String password, String firstName, String lastName, String email) throws SQLException {
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD)) {

            if (isUsernameExists(connection, username)) {
                return "Username already exists.";
            } else {
                String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
                insertUser(connection, username, hashedPassword, firstName, lastName, email);
                return "Registration succeeded.";
            }
        }
    }

    private static boolean isUsernameExists(Connection connection, String username) throws SQLException {
        String query = "SELECT 1 FROM users WHERE username = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setString(1, username);
            ResultSet resultSet = stmt.executeQuery();
            return resultSet.next();
        }
    }

    private static void insertUser(Connection connection, String username, String hashedPassword, String firstName, String lastName, String email) throws SQLException {
        String query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.setString(3, firstName);
            stmt.setString(4, lastName);
            stmt.setString(5, email);
            stmt.executeUpdate();
        }
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure you have the `jbcrypt` library in your classpath for password hashing. You can add it using Maven by including:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


Ensure your database schema includes a `users` table with columns: `username`, `password`, `first_name`, `last_name`, and `email`.