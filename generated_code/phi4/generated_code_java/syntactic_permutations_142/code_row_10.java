import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email to unsubscribe: ");
        String email = scanner.nextLine();
        
        UnsubscribeService service = new UnsubscribeService();
        boolean result = service.unsubscribe(email);

        if (result) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Email address not found in the database.");
        }

        scanner.close();
    }

    public boolean unsubscribe(String email) {
        String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        String sqlDelete = "DELETE FROM subscribers WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement checkStmt = conn.prepareStatement(sqlCheck)) {

            checkStmt.setString(1, email);

            try (ResultSet resultSet = checkStmt.executeQuery()) {
                if (resultSet.next() && resultSet.getInt(1) > 0) {
                    try (PreparedStatement deleteStmt = conn.prepareStatement(sqlDelete)) {
                        deleteStmt.setString(1, email);
                        deleteStmt.executeUpdate();
                        return true;
                    }
                } else {
                    return false;
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}
