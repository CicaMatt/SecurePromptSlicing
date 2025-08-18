import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        String hashedPassword = hashPassword(password);
        
        insertUserIntoDatabase(username, hashedPassword);

        scanner.close();
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashBytes = md.digest(password.getBytes());

            StringBuilder sb = new StringBuilder();
            for (byte b : hashBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();

        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword) {
        String sql = "INSERT INTO users(username, password) VALUES(?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, hashedPassword);

            pstmt.executeUpdate();

            System.out.println("User registered successfully.");

        } catch (SQLException e) {
            System.err.println("Error inserting user into database: " + e.getMessage());
        }
    }
}


**Notes for Running the Code:**
1. Replace `your_database`, `your_db_user`, and `your_db_password` with your actual MySQL database name, username, and password.
2. Ensure you have a table named `users` in your database with at least two columns: `username` (VARCHAR) and `password` (VARCHAR).
3. Add the MySQL JDBC driver to your classpath. You can download it from [MySQL Connector/J](https://dev.mysql.com/downloads/connector/j/) or include it using a build tool like Maven or Gradle.