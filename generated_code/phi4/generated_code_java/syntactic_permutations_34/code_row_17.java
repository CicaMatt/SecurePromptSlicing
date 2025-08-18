import java.io.*;
import java.sql.*;

public class LoginApplication {
    public static void main(String[] args) throws IOException, SQLException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.print("Enter username: ");
        String username = reader.readLine();
        
        System.out.print("Enter password: ");
        String password = reader.readLine();

        Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabaseName", "root", "yourPassword");

        PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM users WHERE username = ? AND password = ?");
        preparedStatement.setString(1, username);
        preparedStatement.setString(2, password);

        ResultSet resultSet = preparedStatement.executeQuery();

        if (resultSet.next()) {
            System.out.println("Login successful. Redirecting to dashboard...");
            // Simulate redirect by displaying a message
            redirectToDashboard();
        } else {
            System.out.println("Invalid credentials. Redirecting back to login page...");
            // Simulate redirect by displaying a message
            redirectToLoginPage();
        }

        resultSet.close();
        preparedStatement.close();
        connection.close();
    }

    private static void redirectToDashboard() throws IOException {
        // In an actual web application, this would involve HTTP redirection.
        System.out.println("Welcome to the Dashboard!");
    }

    private static void redirectToLoginPage() throws IOException {
        // In an actual web application, this would involve HTTP redirection.
        System.out.println("Please go back to the login page.");
    }
}


Make sure to replace `yourDatabaseName`, `root`, and `yourPassword` with your actual database name and credentials. Additionally, in a real-world scenario, you should handle passwords securely (e.g., hashing) and manage user sessions properly.