import java.sql.*;

public class Unsubscribe {
    public static void main(String[] args) {
        String email = "example@example.com";
        unsubscribe(email);
    }
    
    private static void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/dbname", "username", "password"); Statement stmt = conn.createStatement();){
            String sql = "SELECT * FROM email_list WHERE email='" + email + "'";
            ResultSet rs = stmt.executeQuery(sql);
            
            if (rs.next()) {
                String sql2 = "DELETE FROM email_list WHERE email='" + email + "'";
                stmt.executeUpdate(sql2);
                System.out.println("You have been unsubscribed.");
            } else {
                System.out.println("You were never subscribed to begin with.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}