import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginApplication {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Database credentials and URL
        String dbUrl = "jdbc:mysql://localhost:3306/mydatabase";
        String user = "root";
        String password = "password";

        System.out.print("Enter username: ");
        String enteredUsername = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String enteredPassword = scanner.nextLine();

        if (authenticateUser(enteredUsername, enteredPassword, dbUrl, user, password)) {
            System.out.println("Login successful! Redirecting to dashboard...");
            // Redirect to dashboard logic here
        } else {
            System.out.println("Invalid username or password. Redirecting back to login page...");
            // Logic to redirect back to the login page
        }
    }

    private static boolean authenticateUser(String username, String password, String dbUrl, String user, String pass) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(dbUrl, user, pass);

            String sqlQuery = "SELECT * FROM users WHERE username = ? AND password = ?";
            preparedStatement = connection.prepareStatement(sqlQuery);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return true;
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return false;
    }
}
