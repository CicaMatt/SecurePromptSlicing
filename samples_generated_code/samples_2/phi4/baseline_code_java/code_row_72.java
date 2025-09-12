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

        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);
                pstmt.executeUpdate();
                System.out.println("User registered successfully.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            System.out.println("Error registering user: " + e.getMessage());
        }

        scanner.close();
    }
}


**Dependencies**: You need to include the BCrypt library in your project. If you're using Maven, add this dependency to your `pom.xml`:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


**Database Setup**: Ensure you have a MySQL database running and replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Create a table named `users` with columns `username` (VARCHAR) and `password` (VARCHAR).