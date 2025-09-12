import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginApplication {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "root";
    private static final String PASSWORD = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }

        scanner.close();
    }

    private static boolean authenticate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);

            ResultSet resultSet = preparedStatement.executeQuery();

            return resultSet.next();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static void redirectToDashboard() {
        System.out.println("Login successful! Redirecting to dashboard...");
        // Logic to redirect to the dashboard
    }

    private static void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting back to login page...");
        // Logic to redirect back to the login page
    }
}


**Note:** Replace `yourdatabase`, `root`, and `password` with your actual database name, username, and password. Ensure that MySQL JDBC Driver is included in your project's classpath.