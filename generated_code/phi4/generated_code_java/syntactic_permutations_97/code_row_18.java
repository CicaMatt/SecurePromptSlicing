import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;
import org.mindrot.jbcrypt.BCrypt;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        System.out.print("Enter first name: ");
        String firstName = scanner.nextLine();
        
        System.out.print("Enter last name: ");
        String lastName = scanner.nextLine();
        
        System.out.print("Enter email: ");
        String email = scanner.nextLine();

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!isUsernameExists(connection, username)) {
                String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
                insertUser(connection, username, hashedPassword, firstName, lastName, email);
                System.out.println("Registration succeeded.");
            } else {
                System.out.println("The username already exists.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    private static boolean isUsernameExists(Connection connection, String username) throws SQLException {
        String sql = "SELECT 1 FROM users WHERE username = ?";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, username);
            ResultSet resultSet = statement.executeQuery();
            return resultSet.next();
        }
    }

    private static void insertUser(Connection connection, String username, String hashedPassword, 
                                   String firstName, String lastName, String email) throws SQLException {
        String sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, username);
            statement.setString(2, hashedPassword);
            statement.setString(3, firstName);
            statement.setString(4, lastName);
            statement.setString(5, email);
            statement.executeUpdate();
        }
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with the actual database name, username, and password. Also, ensure that your MySQL server is running and accessible at `localhost:3306`. The `users` table should be created in your database with columns matching those used in the SQL statements (`username`, `password`, `first_name`, `last_name`, `email`).