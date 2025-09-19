import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;
import org.mindrot.jbcrypt.BCrypt;

public class UserRegistration {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        // Hash the password
        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        // Database connection details
        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUser = "your_db_user";
        String dbPassword = "your_db_password";

        try (Connection connection = DriverManager.getConnection(url, dbUser, dbPassword)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.executeUpdate();
                System.out.println("User registered successfully.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        scanner.close();
    }
}
