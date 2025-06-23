import java.sql.*;

public class Unsubscribe {
    public static void unsubscribe(String email) throws SQLException {
        String url = "jdbc:mysql://localhost/";  // The JDBC Connector Class.
        Connection con = DriverManager.getConnection(url, "root", "admin");  // Creating the connection object

        PreparedStatement ps = con.prepareStatement("DELETE FROM subscribers WHERE email = ?");  // Using prepared statements to prevent SQL Injection
        ps.setString(1, email);
        
        if (ps.executeUpdate() == 0) {
            System.out.println("You are not in the database.");
        } else {
            System.out.println("You have been unsubscribed.");
        }

        con.close();
    }
}