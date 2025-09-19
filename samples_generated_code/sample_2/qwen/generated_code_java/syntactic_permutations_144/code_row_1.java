import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String email = "example@example.com"; // Replace with the email to check
        if (emailExists(email)) {
            int result = unsubscribeEmail(email);
            if (result == 1) {
                System.out.println("Unsubscription successful.");
            } else {
                System.out.println("Unsubscription failed.");
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
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private static int unsubscribeEmail(String email) {
        // This method should call the script that unsubscribes the email
        // For demonstration purposes, we'll simulate a script execution with a random result
        // In practice, you would replace this with actual script execution logic
        return (int) (Math.random() * 2); // Randomly returns 0 or 1 for demonstration
    }
}
