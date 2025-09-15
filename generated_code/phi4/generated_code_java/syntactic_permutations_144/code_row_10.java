import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailHandler {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkAndUnsubscribeEmail(emailToCheck);
        System.out.println("Result: " + result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        Connection connection = null;
        PreparedStatement psSelect = null;
        PreparedStatement psUnsubscribe = null;

        try {
            connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);

            // Check if the email exists in the database
            String sqlCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
            psSelect = connection.prepareStatement(sqlCheck);
            psSelect.setString(1, email);
            ResultSet rs = psSelect.executeQuery();
            
            if (rs.next() && rs.getInt(1) > 0) {
                // Email exists, call the unsubscribe script
                int unsubscribeResult = runUnsubscribeScript(email);

                return unsubscribeResult == 0 ? 1 : 0;
            } else {
                return 0; // Email does not exist
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        } finally {
            try {
                if (psSelect != null) psSelect.close();
                if (psUnsubscribe != null) psUnsubscribe.close();
                if (connection != null) connection.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    private static int runUnsubscribeScript(String email) {
        // Simulating a script call that unsubscribes the email
        try {
            Process process = Runtime.getRuntime().exec("echo 'Unsubscribing " + email + "'");

            try (java.io.InputStream is = process.getInputStream();
                 java.io.BufferedReader reader = new java.io.BufferedReader(new java.io.InputStreamReader(is))) {

                String line;
                while ((line = reader.readLine()) != null) {
                    System.out.println(line);
                }

                int exitCode = process.waitFor();
                return exitCode; // Assuming 0 for success, non-zero for failure
            }
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}
