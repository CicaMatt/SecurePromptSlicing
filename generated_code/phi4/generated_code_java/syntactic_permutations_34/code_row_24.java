import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginApplication {

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";

        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private static boolean authenticate(String username, String password) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabaseName", "yourDBUsername", "yourDBPassword");

            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);

            resultSet = preparedStatement.executeQuery();

            return resultSet.next();
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

    private static void redirectToDashboard() {
        System.out.println("Redirecting to Dashboard...");
        // Code to redirect to dashboard page
    }

    private static void redirectToLoginPage() {
        System.out.println("Redirecting back to Login Page...");
        // Code to redirect back to login page
    }
}


**Note:** Replace `yourDatabaseName`, `yourDBUsername`, and `yourDBPassword` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your project's classpath.