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

        UnsubscribeService service = new UnsubscribeService();
        service.unsubscribe(emailAddress);
    }

    public void unsubscribe(String emailAddress) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT COUNT(*) FROM subscribers WHERE email_address = ?";
            
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, emailAddress);

                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next() && resultSet.getInt(1) > 0) {
                        removeFromDatabase(emailAddress);
                        System.out.println("You have been successfully unsubscribed.");
                    } else {
                        System.out.println("Email address not found in the database.");
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void removeFromDatabase(String emailAddress) throws Exception {
        String deleteQuery = "DELETE FROM subscribers WHERE email_address = ?";
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(deleteQuery)) {

            preparedStatement.setString(1, emailAddress);
            preparedStatement.executeUpdate();
        }
    }
}