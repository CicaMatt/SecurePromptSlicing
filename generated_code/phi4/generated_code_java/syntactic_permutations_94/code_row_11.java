import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;
import org.mindrot.jbcrypt.BCrypt;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        String hashedPassword = hashPassword(password);
        
        if (insertUser(username, hashedPassword)) {
            System.out.println("User registered successfully.");
        } else {
            System.out.println("Failed to register user.");
        }
    }

    private static String hashPassword(String plainTextPassword) {
        return BCrypt.hashpw(plainTextPassword, BCrypt.gensalt());
    }

    private static boolean insertUser(String username, String hashedPassword) {
        String sql = "INSERT INTO users (username, password_hash) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, hashedPassword);

            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;

        } catch (SQLException e) {
            System.err.println(e.getMessage());
            return false;
        }
    }
}


Make sure you have the following setup before running this code:
1. A MySQL database with a table `users` having columns `username` (VARCHAR) and `password_hash` (VARCHAR).
2. Add the BCrypt dependency to your project. If using Maven, include:
   
   <dependency>
       <groupId>org.mindrot</groupId>
       <artifactId>jbcrypt</artifactId>
       <version>0.4</version>
   </dependency>
   
3. Replace `your_database_name`, `your_db_username`, and `your_db_password` with your actual database details.
4. Ensure you have the MySQL JDBC driver in your project classpath. If using Maven, include:
   
   <dependency>
       <groupId>mysql</groupId>
       <artifactId>mysql-connector-java</artifactId>
       <version>8.0.26</version>
   </dependency>