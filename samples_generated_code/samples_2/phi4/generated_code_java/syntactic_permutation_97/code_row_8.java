import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.xml.bind.DatatypeConverter;
import org.mindrot.jbcrypt.BCrypt;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "newUser";
        String password = "securePassword123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        register(username, password, firstName, lastName, email);
    }

    public static void register(String username, String password, String firstName, String lastName, String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            if (isUsernameExists(conn, username)) {
                System.out.println("The username already exists.");
                return;
            }

            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
            
            String sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.setString(3, firstName);
                statement.setString(4, lastName);
                statement.setString(5, email);

                int rowsInserted = statement.executeUpdate();
                
                if (rowsInserted > 0) {
                    System.out.println("A new user has been registered successfully!");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean isUsernameExists(Connection conn, String username) throws SQLException {
        String sql = "SELECT COUNT(*) FROM users WHERE username = ?";
        
        try (PreparedStatement statement = conn.prepareStatement(sql)) {
            statement.setString(1, username);
            
            ResultSet resultSet = statement.executeQuery();
            
            if (resultSet.next()) {
                return resultSet.getInt(1) > 0;
            }
        }
        
        return false;
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Also, ensure that the MySQL JDBC driver is included in your project dependencies for this code to run properly.