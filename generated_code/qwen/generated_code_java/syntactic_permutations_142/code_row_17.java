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
        scanner.close();
    }

    private static void unsubscribe(String email) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Assuming you are using MySQL and have a database named 'newsletter'
            String url = "jdbc:mysql://localhost:3306/newsletter";
            String user = "root";
            String password = "";

            connection = DriverManager.getConnection(url, user, password);

            String query = "SELECT * FROM subscribers WHERE email = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, email);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                // Email found, proceed to delete
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deleteStatement = connection.prepareStatement(deleteQuery);
                deleteStatement.setString(1, email);
                int rowsAffected = deleteStatement.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                } else {
                    System.out.println("An error occurred while trying to unsubscribe.");
                }
            } else {
                // Email not found
                System.out.println("Email address not found in the database.");
            }

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
    }
}