import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        
        if (emailExists(emailToCheck)) {
            int result = unsubscribeEmail(emailToCheck);
            
            if (result == 1) {
                System.out.println("Unsubscribed successfully.");
            } else {
                System.out.println("Failed to unsubscribe the email.");
            }
        } else {
            System.out.println("Email does not exist in database.");
        }
    }

    private static boolean emailExists(String email) {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setString(1, email);
            
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return false;
    }

    private static int unsubscribeEmail(String email) {
        // This is a placeholder for calling an external script.
        // Replace with actual call to the script and handle its output accordingly.
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("path/to/unsubscribeScript.sh", email);
            Process process = processBuilder.start();
            
            int exitCode = process.waitFor();

            if (exitCode == 0) {
                return 1; // Assuming the script returns 0 on success
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return 0;
    }
}


**Note:** Replace `"jdbc:mysql://localhost:3306/yourDatabase"`, `"username"`, and `"password"` with your actual database URL, username, and password. Also, replace `"path/to/unsubscribeScript.sh"` with the path to your unsubscribe script.