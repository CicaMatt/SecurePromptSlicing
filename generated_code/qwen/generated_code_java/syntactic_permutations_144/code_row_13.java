import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribing {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String email = "example@example.com"; // Replace with actual email to check

        if (emailExists(email)) {
            int result = unsubscribeEmail(email);
            if (result == 1) {
                System.out.println("Email unsubscribed successfully.");
            } else {
                System.out.println("Failed to unsubscribe email.");
            }
        } else {
            System.out.println("Email does not exist in the database.");
        }
    }

    private static boolean emailExists(String email) {
        String query = "SELECT 1 FROM users WHERE email = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            return rs.next();

        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    private static int unsubscribeEmail(String email) {
        // Assuming there is a script that can be called via command line
        ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribe_script.sh", email);
        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1; // Return -1 to indicate an error
    }
}