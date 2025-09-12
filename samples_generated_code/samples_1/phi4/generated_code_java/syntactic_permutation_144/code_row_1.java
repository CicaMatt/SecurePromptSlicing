import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class EmailChecker {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        checkAndUnsubscribeEmail(emailToCheck);
    }

    private static void checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!emailExists(conn, email)) {
                System.out.println("Email does not exist in the database.");
            } else {
                int result = unsubscribeEmail(email);
                if (result == 1) {
                    System.out.println("Unsubscription successful.");
                } else {
                    System.out.println("Failed to unsubscribe email.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean emailExists(Connection conn, String email) throws Exception {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    private static int unsubscribeEmail(String email) throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe_script.sh", email);
        Process process = processBuilder.start();
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        StringBuilder output = new StringBuilder();

        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = process.waitFor();
        System.out.println("Script Output: " + output);

        return exitCode == 0 ? 1 : 0; // Assuming the script returns 0 on success.
    }
}


Make sure to replace `your_database`, `your_username`, `your_password`, and `path/to/unsubscribe_script.sh` with your actual database details and script path.