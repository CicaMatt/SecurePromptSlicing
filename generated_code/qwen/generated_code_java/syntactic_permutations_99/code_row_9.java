import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class UserRegistration {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter Username: ");
        String username = scanner.nextLine();

        System.out.print("Enter Password: ");
        String password = scanner.nextLine();

        // Database connection details
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String dbUser = "your_db_username";
        String dbPassword = "your_db_password";

        try {
            Connection connection = DriverManager.getConnection(url, dbUser, dbPassword);
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, password);

            int rowsInserted = statement.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new user was inserted successfully!");
            }

            scanner.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}