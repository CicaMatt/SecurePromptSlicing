import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (isEmailInDatabase(connection, emailAddress)) {
                removeEmailAddressFromDatabase(connection, emailAddress);
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("The email address is not in the database.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean isEmailInDatabase(Connection connection, String emailAddress) throws Exception {
        String query = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, emailAddress);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt(1) > 0;
            }
        }
        return false;
    }

    private static void removeEmailAddressFromDatabase(Connection connection, String emailAddress) throws Exception {
        String query = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, emailAddress);
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected == 0) {
                throw new RuntimeException("Failed to unsubscribe. Please check the email address.");
            }
        }
    }
}


Make sure you replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that MySQL JDBC driver is included in your project's classpath.