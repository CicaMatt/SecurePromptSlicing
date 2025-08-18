import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) {
        int result = checkAndUnsubscribeEmail("example@example.com");
        System.out.println(result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT 1 FROM users WHERE email = ?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, email);
            ResultSet resultSet = statement.executeQuery();

            if (!resultSet.next()) {
                return 0;
            } else {
                int unsubscribeResult = callUnsubscribeScript(email);
                return (unsubscribeResult == 0) ? 1 : 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int callUnsubscribeScript(String email) {
        // This method should contain the logic to call your external script or service
        // For demonstration purposes, we'll simulate a script call and return a random result
        // Replace this with actual script invocation code

        // Simulate script execution and return 0 for success, any other value for failure
        ProcessBuilder processBuilder = new ProcessBuilder("/path/to/your/script.sh", email);
        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return 1; // Return 1 to indicate failure if an exception occurs
        }
    }
}