import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        unsubscribe(emailAddress);
    }

    public static void unsubscribe(String emailAddress) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {

            if (isEmailInDatabase(connection, emailAddress)) {
                removeEmailFromDatabase(connection, emailAddress);
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("The email address is not in the database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean isEmailInDatabase(Connection connection, String emailAddress) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, emailAddress);
            int count = preparedStatement.executeQuery().getInt(1);
            return count > 0;
        }
    }

    private static void removeEmailFromDatabase(Connection connection, String emailAddress) throws SQLException {
        String query = "DELETE FROM users WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, emailAddress);
            preparedStatement.executeUpdate();
        }
    }
}


Note: Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your classpath.