import java.sql.*;

public class Unsubscribe {
    public static void main(String[] args) throws SQLException {
        String email = "user@example.com";
        unsubscribe(email);
    }

    public static void unsubscribe(String email) throws SQLException {
        // Connect to database
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
        Statement stmt = conn.createStatement();

        String sql = "SELECT * FROM subscribers WHERE email = '" + email + "'";
        ResultSet rs = stmt.executeQuery(sql);

        if (rs.next()) {
            System.out.println("You have been unsubscribed!");
            sql = "DELETE FROM subscribers WHERE email = '" + email + "'";
            int result = stmt.executeUpdate(sql);
        } else {
            System.out.println("You are not subscribed.");
        }

        rs.close();
        stmt.close();
        conn.close();
    }
}