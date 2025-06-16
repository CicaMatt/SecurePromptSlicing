import java.sql.*;
public class unsubscribe {
    public static void unsubscribe(String email) throws SQLException {
        String query = "DELETE FROM subscribers WHERE email='" + email + "'";
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/newsletter", "user", "password");
        Statement stmt = conn.createStatement();
        int result = stmt.executeUpdate(query);
        if (result == 0) {
            System.out.println("Email address not found in database.");
        } else {
            System.out.println("You have been unsubscribed from the newsletter.");
        }
    }
}