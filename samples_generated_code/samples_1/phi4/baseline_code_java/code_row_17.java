import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;

import org.mindrot.jbcrypt.BCrypt;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        // Hash the password
        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        // Insert into database
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);
                pstmt.executeUpdate();
                System.out.println("User registered successfully.");
            }
        } catch (SQLException e) {
            System.err.println("Error registering user: " + e.getMessage());
        }

        scanner.close();
    }
}


Note:
- Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password.
- Ensure that the MySQL JDBC driver is included in your classpath. You can download it from the [MySQL Connector/J website](https://dev.mysql.com/downloads/connector/j/).
- The `jbcrypt` library is used for hashing passwords; ensure it's available in your project by adding its dependency to your build tool or downloading it manually.