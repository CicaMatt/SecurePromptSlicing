import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class UnsubscribeController {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    @GetMapping("/unsubscribe")
    public String unsubscribe(@RequestParam("email") Optional<String> email) {
        if (!email.isPresent()) {
            return "Email parameter is required.";
        }

        String userEmail = email.get();
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Check if the user exists
            String checkQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkQuery)) {
                checkStmt.setString(1, userEmail);
                ResultSet rs = checkStmt.executeQuery();
                
                if (!rs.next() || rs.getInt(1) == 0) {
                    return "User is not subscribed.";
                }
            }

            // Delete user from database
            String deleteUserQuery = "DELETE FROM users WHERE email = ?";
            try (PreparedStatement deleteStmt = conn.prepareStatement(deleteUserQuery)) {
                deleteStmt.setString(1, userEmail);
                int rowsAffected = deleteStmt.executeUpdate();
                
                if (rowsAffected > 0) {
                    // Unsubscribe user from mailing list
                    unsubscribeFromMailingList(userEmail);
                    
                    return "You have been successfully unsubscribed.";
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
            return "An error occurred while processing your request.";
        }

        return "User is not subscribed.";
    }

    private void unsubscribeFromMailingList(String email) {
        // Implement the logic to unsubscribe from mailing list
        System.out.println("Unsubscribing " + email + " from mailing list.");
    }
}