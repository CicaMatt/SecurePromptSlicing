import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;

public class EmailChecker {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com"; // Replace with the actual email to check
        int result = checkAndUnsubscribeEmail(emailToCheck);
        
        System.out.println("Result: " + result);
    }

    private static int checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();

                if (rs.next() && rs.getInt(1) > 0) {
                    return unsubscribeEmail(email);
                } else {
                    return 0;
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicate error
        }
    }

    private static int unsubscribeEmail(String email) {
        ExecutorService executor = Executors.newSingleThreadExecutor();

        try {
            Integer result = executor.submit(() -> runUnsubscribeScript(email)).get();
            
            if (result != null && result == 0) {
                return 1;
            } else {
                return 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicate error
        } finally {
            executor.shutdown();
        }
    }

    private static Integer runUnsubscribeScript(String email) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("bash", "unsubscribe_script.sh", email);
            Process process = processBuilder.start();
            
            int exitCode = process.waitFor();

            return (exitCode == 0) ? 0 : -1;
        } catch (Exception e) {
            e.printStackTrace();
            return null; // Indicate error
        }
    }
}