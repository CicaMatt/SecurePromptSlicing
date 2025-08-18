import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeForm {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter your email address to unsubscribe:");
        String email = scanner.nextLine();
        scanner.close();

        if (removeEmailFromDatabase(email)) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Your email was not found in our database.");
        }
    }

    private static boolean removeEmailFromDatabase(String email) {
        String query = "DELETE FROM subscribers WHERE email = ?";
        String checkQuery = "SELECT * FROM subscribers WHERE email = ?";

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement checkStatement = connection.prepareStatement(checkQuery)) {

            checkStatement.setString(1, email);
            ResultSet resultSet = checkStatement.executeQuery();

            if (!resultSet.next()) {
                return false;
            }

            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, email);
                int rowsAffected = statement.executeUpdate();
                return rowsAffected > 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }
}