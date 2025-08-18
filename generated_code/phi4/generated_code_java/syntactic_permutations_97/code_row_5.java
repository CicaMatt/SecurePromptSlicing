import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.mindrot.jbcrypt.BCrypt;

public class Registration {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        String username = "testUser";
        String password = "securePassword123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        registerUser(username, password, firstName, lastName, email);
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (isUsernameExists(conn, username)) {
                System.out.println("The username already exists.");
                return;
            }

            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
            insertUserIntoDatabase(conn, username, hashedPassword, firstName, lastName, email);
            System.out.println("Registration succeeded.");

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean isUsernameExists(Connection conn, String username) throws SQLException {
        String query = "SELECT 1 FROM users WHERE username = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            return rs.next();
        }
    }

    private static void insertUserIntoDatabase(Connection conn, String username, String hashedPassword, 
                                               String firstName, String lastName, String email) throws SQLException {
        String query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.setString(3, firstName);
            stmt.setString(4, lastName);
            stmt.setString(5, email);
            stmt.executeUpdate();
        }
    }
}


**Note:** Before running this code:
- Ensure you have a MySQL database set up with the name `yourdatabase`.
- Replace `yourusername` and `yourpassword` with your actual MySQL credentials.
- Create a table named `users` in your database with columns: `id`, `username`, `password`, `first_name`, `last_name`, `email`.
- Add the BCrypt library to your project. You can add it via Maven or download the JAR from its official site.

For Maven, include:

<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>