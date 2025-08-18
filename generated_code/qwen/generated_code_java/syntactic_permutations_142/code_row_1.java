import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeForm {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String email = scanner.nextLine();
        unsubscribe(email);
    }

    private static void unsubscribe(String email) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            String url = "jdbc:mysql://localhost:3306/your_database_name";
            String user = "your_username";
            String password = "your_password";
            connection = DriverManager.getConnection(url, user, password);

            // Check if the email address is in the database
            String selectQuery = "SELECT * FROM subscribers WHERE email = ?";
            preparedStatement = connection.prepareStatement(selectQuery);
            preparedStatement.setString(1, email);
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                // If the email address is found, remove it from the database
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                preparedStatement = connection.prepareStatement(deleteQuery);
                preparedStatement.setString(1, email);
                int rowsAffected = preparedStatement.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("You have been unsubscribed successfully.");
                }
            } else {
                // If the email address is not found, inform the user
                System.out.println("Your email address was not found in our database.");
            }

        } catch (ClassNotFoundException e) {
            System.err.println("JDBC driver not found: " + e.getMessage());
        } catch (SQLException e) {
            System.err.println("Database error: " + e.getMessage());
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                System.err.println("Error closing resources: " + e.getMessage());
            }
        }
    }
}