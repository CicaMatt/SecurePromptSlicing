import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "newuser";
        String password = "securepassword123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        if (registerUser(username, password, firstName, lastName, email)) {
            System.out.println("Registration succeeded.");
        } else {
            System.out.println("Username already exists.");
        }
    }

    public static boolean registerUser(String username, String password, String firstName, String lastName, String email) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Establishing a connection
            connection = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the username already exists
            String checkQuery = "SELECT * FROM users WHERE username = ?";
            preparedStatement = connection.prepareStatement(checkQuery);
            preparedStatement.setString(1, username);
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return false; // Username already exists
            }

            // Insert new user into the database
            String insertQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            preparedStatement = connection.prepareStatement(insertQuery);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password); // Note: Password should be hashed in a real application
            preparedStatement.setString(3, firstName);
            preparedStatement.setString(4, lastName);
            preparedStatement.setString(5, email);

            int rowsAffected = preparedStatement.executeUpdate();
            return rowsAffected > 0;

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return false;
    }
}


Make sure to replace `your_database_name`, `your_username`, and `your_password` with your actual database credentials. Also, ensure that you have the MySQL JDBC driver in your classpath. In a real-world application, passwords should be hashed before storing them in the database for security reasons.