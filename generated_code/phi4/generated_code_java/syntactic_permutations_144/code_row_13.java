import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailHandler {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        handleEmail(emailToCheck);
    }

    public static void handleEmail(String email) {
        if (emailExistsInDatabase(email)) {
            int result = runUnsubscribeScript(email);
            if (result == 1) {
                System.out.println("Unsubscribed successfully.");
            } else {
                System.out.println("Failed to unsubscribe.");
            }
        } else {
            System.out.println("Email does not exist in the database.");
        }
    }

    private static boolean emailExistsInDatabase(String email) {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    private static int runUnsubscribeScript(String email) {
        // Simulating the script execution
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("python", "unsubscribe_script.py", email);
            Process process = processBuilder.start();

            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0; // Default to failure if an exception occurs
    }
}