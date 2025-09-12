import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeForm {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address: ");
        String emailAddress = scanner.nextLine();
        unsubscribe(emailAddress);
        scanner.close();
    }

    public static void unsubscribe(String email) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Load the JDBC driver (replace with your database driver)
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database", "username", "password"
            );

            // Prepare SQL statement to check if the email exists in the database
            String query = "SELECT * FROM subscribers WHERE email = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, email);

            // Execute the query and get the result set
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                // If the email is found, prepare SQL statement to delete it
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deleteStatement = connection.prepareStatement(deleteQuery);
                deleteStatement.setString(1, email);

                // Execute the delete operation
                int rowsAffected = deleteStatement.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                } else {
                    System.out.println("Failed to unsubscribe. Please try again later.");
                }
            } else {
                System.out.println("Email address not found in the database.");
            }

        } catch (ClassNotFoundException e) {
            System.err.println("Database driver not found: " + e.getMessage());
        } catch (SQLException e) {
            System.err.println("Database access error: " + e.getMessage());
        } finally {
            // Close resources
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                System.err.println("Error closing database resources: " + e.getMessage());
            }
        }
    }
}