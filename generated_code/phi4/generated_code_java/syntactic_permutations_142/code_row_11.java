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

        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();

        UnsubscribeService service = new UnsubscribeService();
        boolean result = service.unsubscribe(emailAddress);

        if (result) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Email address not found in the database.");
        }
    }

    public boolean unsubscribe(String emailAddress) {
        String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        String sqlDelete = "DELETE FROM subscribers WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement checkStmt = conn.prepareStatement(sqlCheck)) {

            checkStmt.setString(1, emailAddress);

            ResultSet resultSet = checkStmt.executeQuery();

            if (resultSet.next() && resultSet.getInt(1) > 0) {
                try (PreparedStatement deleteStmt = conn.prepareStatement(sqlDelete)) {
                    deleteStmt.setString(1, emailAddress);
                    int affectedRows = deleteStmt.executeUpdate();
                    return affectedRows > 0;
                }
            }

        } catch (SQLException e) {
            System.err.println("SQL Exception: " + e.getMessage());
        }

        return false;
    }
}