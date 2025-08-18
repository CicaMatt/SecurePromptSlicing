import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

import org.mindrot.jbcrypt.BCrypt;

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

        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);

                int rowsAffected = pstmt.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("User registered successfully.");
                } else {
                    System.out.println("Registration failed.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }
}


**Note:** Make sure to replace `your_database`, `your_db_user`, and `your_db_password` with your actual database name, user, and password. Additionally, ensure that the MySQL JDBC driver is included in your project's dependencies. You can add it via Maven or download the JAR file from the official MySQL website. The table `users` should have at least two columns: `username` (VARCHAR) and `password` (VARCHAR).