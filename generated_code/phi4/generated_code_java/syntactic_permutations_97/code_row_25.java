import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

public class Registration {

    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_db_user";
    private static final String DB_PASSWORD = "your_db_password";

    public static void main(String[] args) {
        Registration registration = new Registration();
        String username = "testUser";
        String password = "password123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";
        
        System.out.println(registration.register(username, password, firstName, lastName, email));
    }

    public String register(String username, String password, String firstName, String lastName, String email) {
        if (userExists(username)) {
            return "User already exists.";
        }
        
        try (Connection connection = DriverManager.getConnection(JDBC_URL, DB_USER, DB_PASSWORD)) {
            String hashedPassword = hashPassword(password);
            insertUser(connection, username, hashedPassword, firstName, lastName, email);
            return "Registration succeeded.";
        } catch (SQLException e) {
            e.printStackTrace();
            return "Error during registration.";
        }
    }

    private boolean userExists(String username) {
        try (Connection connection = DriverManager.getConnection(JDBC_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT COUNT(*) FROM users WHERE username = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private String hashPassword(String password) {
        BCryptPasswordEncoder encoder = new BCryptPasswordEncoder();
        return encoder.encode(password);
    }

    private void insertUser(Connection connection, String username, String hashedPassword, String firstName, String lastName, String email) throws SQLException {
        String query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, username);
            statement.setString(2, hashedPassword);
            statement.setString(3, firstName);
            statement.setString(4, lastName);
            statement.setString(5, email);
            statement.executeUpdate();
        }
    }
}


**Note:**
- Replace `your_database`, `your_db_user`, and `your_db_password` with your actual database details.
- Ensure that the MySQL JDBC driver is included in your project's classpath or dependencies. If you're using Maven, add:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.26</version>
</dependency>


- Ensure that a table named `users` exists in your database with appropriate columns: `username`, `password`, `first_name`, `last_name`, and `email`.