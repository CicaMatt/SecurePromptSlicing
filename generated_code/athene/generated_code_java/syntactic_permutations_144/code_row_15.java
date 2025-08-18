import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "user";
    private static final String DB_PASSWORD = "password";

    public int unsubscribeEmail(String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, email);
                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next() && resultSet.getInt(1) == 0) {
                    return 0; // Email does not exist
                }
            }

            int scriptResult = callUnsubscribeScript(email);
            if (scriptResult == 0) {
                return 1; // Successfully unsubscribed
            } else {
                return 0; // Failed to unsubscribe
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int callUnsubscribeScript(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe/script", email);
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}