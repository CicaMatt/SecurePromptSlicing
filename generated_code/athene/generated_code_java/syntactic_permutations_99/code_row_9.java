import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class UserRegistration {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        insertUserIntoDatabase(username, password);

        scanner.close();
    }

    private static void insertUserIntoDatabase(String username, String password) {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String dbUser = "root";
        String dbPassword = "password";

        try (Connection connection = DriverManager.getConnection(url, dbUser, dbPassword)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, password); // Note: In production, hash the password before storing
            statement.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}