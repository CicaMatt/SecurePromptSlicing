import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeForm {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email address to unsubscribe:");
        String email = scanner.nextLine();
        unsubscribe(email);
    }

    private static void unsubscribe(String email) {
        Connection connection = null;
        PreparedStatement checkStmt = null;
        PreparedStatement deleteStmt = null;
        ResultSet resultSet = null;

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database_name", "your_username", "your_password");

            // Check if the email exists in the database
            String checkQuery = "SELECT * FROM subscribers WHERE email = ?";
            checkStmt = connection.prepareStatement(checkQuery);
            checkStmt.setString(1, email);
            resultSet = checkStmt.executeQuery();

            if (resultSet.next()) {
                // Delete the email from the database
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                deleteStmt = connection.prepareStatement(deleteQuery);
                deleteStmt.setString(1, email);
                int affectedRows = deleteStmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                } else {
                    System.out.println("An error occurred while processing your request.");
                }
            } else {
                System.out.println("This email address is not subscribed.");
            }

        } catch (ClassNotFoundException e) {
            System.err.println("JDBC Driver not found.");
        } catch (SQLException e) {
            System.err.println("Database access error: " + e.getMessage());
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (checkStmt != null) checkStmt.close();
                if (deleteStmt != null) deleteStmt.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                System.err.println("Error closing database resources: " + e.getMessage());
            }
        }
    }
}