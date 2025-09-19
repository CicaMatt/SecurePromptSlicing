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
        System.out.print("Enter your email to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        
        UnsubscribeService service = new UnsubscribeService();
        service.unsubscribe(emailAddress);
    }

    public void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!isEmailInDatabase(conn, email)) {
                System.out.println("The email address is not in the database.");
                return;
            }
            
            String sql = "DELETE FROM subscribers WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, email);
                int rowsAffected = stmt.executeUpdate();
                
                if (rowsAffected > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                } else {
                    System.out.println("An error occurred while trying to unsubscribe.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private boolean isEmailInDatabase(Connection conn, String email) throws Exception {
        String sql = "SELECT 1 FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next();
            }
        }
    }
}


**Note**: Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Ensure that the MySQL JDBC driver is included in your project's classpath.