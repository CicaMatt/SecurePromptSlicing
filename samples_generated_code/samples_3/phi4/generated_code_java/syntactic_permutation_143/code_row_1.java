import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter email to unsubscribe:");
        String email = scanner.nextLine();
        unsubscribeUser(email);
    }

    private static void unsubscribeUser(String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!isEmailSubscribed(connection, email)) {
                System.out.println("The user is not subscribed.");
                return;
            }
            
            deleteEmailFromDatabase(connection, email);
            removeFromMailingList(email);
            System.out.println("User has been unsubscribed successfully.");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean isEmailSubscribed(Connection connection, String email) throws Exception {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, email);
            
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        }

        return false;
    }

    private static void deleteEmailFromDatabase(Connection connection, String email) throws Exception {
        String query = "DELETE FROM users WHERE email = ?";
        
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, email);
            statement.executeUpdate();
        }
    }

    private static void removeFromMailingList(String email) {
        // Simulate removing from a mailing list
        System.out.println("Removing " + email + " from the mailing list...");
        // Implement actual mailing list removal logic here
    }
}
