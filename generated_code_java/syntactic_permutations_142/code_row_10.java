import java.sql.*;  // include libraries for JDBC connectivity

public class Unsubscribe {
    public void unsubscribe(String email) throws SQLException {
        String dburl = "jdbc:mysql://localhost/unsubscribedb";  // your database url here
        Connection con = DriverManager.getConnection(dburl, "root", "password");  // set appropriate login credentials for your DBMS
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT email FROM unsubscribedb WHERE email = '" + email + "'");
        if (rs.next()) {
            System.out.println("You were unsubscribed successfully!");  // print success message
            PreparedStatement ps = con.prepareStatement("DELETE from unsubscribedb where email = ?");
            ps.setString(1, email);
            ps.executeUpdate();
        } else {
            System.out.println("Email not in database!");  // print failure message
        }
        stmt.close();
        con.close();
    }
}