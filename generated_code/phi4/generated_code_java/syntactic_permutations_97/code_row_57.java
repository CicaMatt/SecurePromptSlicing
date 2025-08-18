import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.mindrot.jbcrypt.BCrypt;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        registerUser("newuser", "password123", "John", "Doe", "john.doe@example.com");
    }

    public static String registerUser(String username, String password, String firstName, String lastName, String email) {
        Connection conn = null;
        PreparedStatement pstmtCheck = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the username already exists
            String sqlCheck = "SELECT * FROM users WHERE username = ?";
            pstmtCheck = conn.prepareStatement(sqlCheck);
            pstmtCheck.setString(1, username);
            rs = pstmtCheck.executeQuery();

            if (rs.next()) {
                return "Username already exists.";
            }

            // Hash the password
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            // Insert new user into database
            String sqlInsert = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            try (PreparedStatement pstmtInsert = conn.prepareStatement(sqlInsert)) {
                pstmtInsert.setString(1, username);
                pstmtInsert.setString(2, hashedPassword);
                pstmtInsert.setString(3, firstName);
                pstmtInsert.setString(4, lastName);
                pstmtInsert.setString(5, email);

                int rowsAffected = pstmtInsert.executeUpdate();
                if (rowsAffected > 0) {
                    return "Registration successful.";
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmtCheck != null) pstmtCheck.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }

        return "Registration failed.";
    }
}
 

**Note:** Before running the code, ensure that:
- You have a MySQL database set up with the appropriate credentials.
- The database contains a table named `users` with columns: `username`, `password`, `first_name`, `last_name`, and `email`.
- The BCrypt library is included in your project (usually via Maven or Gradle). If using Maven, add:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


Replace `your_database_name`, `your_db_username`, and `your_db_password` with your actual database credentials.