import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter email to unsubscribe: ");
        String email = scanner.nextLine();
        
        UnsubscribeService service = new UnsubscribeService();
        boolean result = service.unsubscribe(email);

        if (result) {
            System.out.println("User unsubscribed successfully.");
        } else {
            System.out.println("User is not subscribed.");
        }
    }

    public boolean unsubscribe(String email) {
        String sqlCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
        String sqlDelete = "DELETE FROM users WHERE email = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement checkStmt = conn.prepareStatement(sqlCheck)) {

            checkStmt.setString(1, email);

            ResultSet rs = checkStmt.executeQuery();
            
            if (rs.next() && rs.getInt(1) > 0) {
                try (PreparedStatement deleteStmt = conn.prepareStatement(sqlDelete)) {
                    deleteStmt.setString(1, email);
                    deleteStmt.executeUpdate();
                    
                    // Additional logic to unsubscribe from mailing list can be added here

                    return true;
                }
            } else {
                return false;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}
