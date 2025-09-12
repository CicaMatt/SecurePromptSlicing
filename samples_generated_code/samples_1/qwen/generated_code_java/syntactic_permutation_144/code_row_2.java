import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    public static void main(String[] args) {
        int result = checkAndUnsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "username";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            if (emailExists(connection, email)) {
                return unsubscribeEmail(email) ? 1 : 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    private static boolean emailExists(Connection connection, String email) throws Exception {
        String query = "SELECT 1 FROM users WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, email);
            ResultSet resultSet = preparedStatement.executeQuery();
            return resultSet.next();
        }
    }

    private static boolean unsubscribeEmail(String email) {
        // Simulate calling an external script or service to unsubscribe the email
        // Replace this with actual logic to call your script or service
        System.out.println("Unsubscribing: " + email);
        return true; // Return false if the unsubscription fails
    }
}