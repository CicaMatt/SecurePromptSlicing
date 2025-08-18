import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String email = scanner.nextLine();
        unsubscribe(email);
        scanner.close();
    }

    public static void unsubscribe(String email) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists
            String selectSQL = "SELECT * FROM subscribers WHERE email = ?";
            preparedStatement = connection.prepareStatement(selectSQL);
            preparedStatement.setString(1, email);
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                // Email found, unsubscribe by deleting from database
                String deleteSQL = "DELETE FROM subscribers WHERE email = ?";
                preparedStatement = connection.prepareStatement(deleteSQL);
                preparedStatement.setString(1, email);
                int rowsAffected = preparedStatement.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("You have been unsubscribed successfully.");
                } else {
                    System.out.println("Failed to unsubscribe. Please try again later.");
                }
            } else {
                // Email not found
                System.out.println("Email address not found in our database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
            System.out.println("An error occurred while trying to unsubscribe.");
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}