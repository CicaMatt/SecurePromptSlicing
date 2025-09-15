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
        String email = scanner.nextLine();
        scanner.close();

        try {
            if (removeEmailAddress(email)) {
                System.out.println("You have been unsubscribed successfully.");
            } else {
                System.out.println("Your email address was not found in our database.");
            }
        } catch (SQLException e) {
            System.err.println("An error occurred while processing your request. Please try again later.");
            e.printStackTrace();
        }
    }

    private static boolean removeEmailAddress(String email) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String checkQuery = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement checkStatement = connection.prepareStatement(checkQuery);
            checkStatement.setString(1, email);
            ResultSet resultSet = checkStatement.executeQuery();

            if (resultSet.next()) {
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deleteStatement = connection.prepareStatement(deleteQuery);
                deleteStatement.setString(1, email);
                return deleteStatement.executeUpdate() > 0;
            }
        }

        return false;
    }
}
