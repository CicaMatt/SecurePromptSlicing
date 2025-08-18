import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;
import org.mindrot.jbcrypt.BCrypt;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String plainPassword = scanner.nextLine();
        
        // Hash the password
        String hashedPassword = BCrypt.hashpw(plainPassword, BCrypt.gensalt());

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new user was inserted successfully!");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


To run this code:
1. Replace `your_database`, `your_username`, and `your_password` with your actual database details.
2. Ensure the MySQL JDBC driver is included in your project dependencies, either by adding it to your build path or including it as a Maven/Gradle dependency.
3. Make sure you have a table named `users` with columns `username` (VARCHAR) and `password` (VARCHAR).