import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email address to unsubscribe:");
        String email = scanner.nextLine();
        unsubscribe(email);
    }

    public static void unsubscribe(String email) {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sqlCheck = "SELECT * FROM subscribers WHERE email = ?";
            stmt = conn.prepareStatement(sqlCheck);
            stmt.setString(1, email);
            rs = stmt.executeQuery();

            if (rs.next()) {
                String sqlDelete = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deleteStmt = conn.prepareStatement(sqlDelete);
                deleteStmt.setString(1, email);
                int rowsDeleted = deleteStmt.executeUpdate();
                if (rowsDeleted > 0) {
                    System.out.println("You have been unsubscribed successfully.");
                }
            } else {
                System.out.println("Your email address is not in the database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}