import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class LoginPage {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            redirectToHomePage();
        } else {
            System.out.println("Login failed. Incorrect password.");
        }

        scanner.close();
    }

    private static boolean login(String username, String password) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUsername = "your_db_username";
        String dbPassword = "your_db_password";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword)) {
            String query = "SELECT password FROM users WHERE username = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, username);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                String storedPassword = resultSet.getString("password");
                return storedPassword.equals(password);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return false;
    }

    private static void redirectToHomePage() {
        System.out.println("Redirecting to Home Page...");
        // Code to redirect to home page
    }
}