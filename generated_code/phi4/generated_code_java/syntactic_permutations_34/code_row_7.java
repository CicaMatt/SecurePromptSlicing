import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (authenticateUser(connection, username, password)) {
                redirectToDashboard();
            } else {
                redirectToLoginPage();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    private static boolean authenticateUser(Connection connection, String username, String password) throws Exception {
        String sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, username);
            statement.setString(2, password);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static void redirectToDashboard() {
        System.out.println("Redirecting to dashboard...");
        // Code to redirect to the dashboard page
    }

    private static void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting back to login page.");
        // Code to redirect back to the login page
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Make sure you have a table named `users` in your database with columns `username` and `password`. Also, ensure that you have the MySQL JDBC driver in your classpath for this code to run successfully.