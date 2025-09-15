import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeService {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        scanner.close();

        try {
            unsubscribe(emailAddress);
        } catch (SQLException e) {
            System.err.println("Database error occurred: " + e.getMessage());
        }
    }

    public static void unsubscribe(String email) throws SQLException {
        if (!isEmailInDatabase(email)) {
            System.out.println("The email address is not in the database.");
            return;
        }

        Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
        String query = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, email);

            int rowsAffected = preparedStatement.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("An error occurred while trying to unsubscribe you. Please try again later.");
            }
        } finally {
            connection.close();
        }
    }

    private static boolean isEmailInDatabase(String email) throws SQLException {
        Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
        String query = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, email);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt(1) > 0;
            }
        } finally {
            connection.close();
        }
        return false;
    }
}
