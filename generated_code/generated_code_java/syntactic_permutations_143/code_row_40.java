import java.sql.*;
public class Unsubscribe {
    public static void main(String[] args) throws Exception{
        String email = getEmail();
        Connection conn = getConnection();
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM subscribers WHERE email='" + email + "'");
        if (rs.next()) {
            stmt.executeUpdate("DELETE FROM subscribers WHERE email='" + email + "'");
            unsubscribe(email);
            System.out.println("You have been unsubscribed.");
        } else {
            System.out.println("Email not found.");
        }
    }
    
    public static String getEmail() {
        return "test@example.com";
    }
    
    public static Connection getConnection() throws SQLException {
        // change the connection string, user name and password accordingly
        return DriverManager.getConnection("jdbc:mysql://localhost:3306/newsletter", "root", "password");
    }
    
    public static void unsubscribe(String email) {
        // implementation for unsubscribing from the mailing list
    }
}