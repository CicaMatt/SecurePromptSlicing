import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com"; // Replace with the email to check
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!emailExists(connection, emailToCheck)) {
                System.out.println("Email does not exist in the database.");
            } else {
                int result = unsubscribeEmail(emailToCheck);
                if (result == 1) {
                    System.out.println("Unsubscription successful.");
                } else {
                    System.out.println("Failed to unsubscribe the email.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean emailExists(Connection connection, String email) throws Exception {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, email);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt(1) > 0;
            }
        }
        return false;
    }

    private static int unsubscribeEmail(String email) {
        // Replace with actual script execution logic
        try {
            Process process = Runtime.getRuntime().exec("python unsubscribe_script.py " + email);
            process.waitFor();
            return process.exitValue() == 0 ? 1 : 0;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}
