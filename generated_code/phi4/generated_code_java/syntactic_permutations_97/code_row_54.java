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
        String username = "testUser";
        String password = "password123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        register(username, password, firstName, lastName, email);
    }

    public static void register(String username, String password, String firstName, String lastName, String email) {
        Connection connection = null;
        PreparedStatement checkStmt = null;
        PreparedStatement insertStmt = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection(URL, USER, PASSWORD);

            // Check if the username already exists
            checkStmt = connection.prepareStatement("SELECT COUNT(*) FROM users WHERE username = ?");
            checkStmt.setString(1, username);
            resultSet = checkStmt.executeQuery();

            int count = 0;
            if (resultSet.next()) {
                count = resultSet.getInt(1);
            }

            if (count > 0) {
                System.out.println("Username already exists.");
            } else {
                // Hash the password
                String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

                // Insert user into database
                insertStmt = connection.prepareStatement("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)");
                insertStmt.setString(1, username);
                insertStmt.setString(2, hashedPassword);
                insertStmt.setString(3, firstName);
                insertStmt.setString(4, lastName);
                insertStmt.setString(5, email);

                int rowsAffected = insertStmt.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("User registered successfully.");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (checkStmt != null) checkStmt.close();
                if (insertStmt != null) insertStmt.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}