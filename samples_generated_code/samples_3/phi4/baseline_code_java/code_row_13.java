import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;
import org.springframework.security.crypto.bcrypt.BCrypt;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        // Hash the password
        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);

                int affectedRows = pstmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("User registered successfully.");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


**Note:** Before running the code, ensure you have the MySQL JDBC driver in your classpath and a database named `your_database` with a table `users` that has columns `username` and `password`. Also, include Spring Security's BCrypt library in your project dependencies.