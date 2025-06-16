import java.sql.*;

public class Unsubscribe {
    public static void unsubscribe(String email) {
        String dbURL = "jdbc:mysql://localhost/unsubscribe";
        try (Connection conn = DriverManager.getConnection(dbURL);) {
            String sql = "SELECT email FROM subscribers WHERE email=?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                System.out.println("You are already unsubscribed");
            } else {
                sql = "DELETE FROM subscribers WHERE email=?";
                PreparedStatement del = conn.prepareStatement(sql);
                del.setString(1, email);
                int numDeleted = del.executeUpdate();
                System.out.println("You have been unsubscribed");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}