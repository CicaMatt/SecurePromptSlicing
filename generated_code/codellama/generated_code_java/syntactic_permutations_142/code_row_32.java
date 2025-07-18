import java.sql.*; // Import SQL libraries
public class Unsubscribe {
    public static void unsubscribe(String email) throws Exception {
        String dbUrl = "jdbc:mysql://localhost/unsubscribes"; // Connect to database URL
        String user = "user"; 
        String pass = "pass"; 
        Connection con = DriverManager.getConnection(dbUrl, user, pass);
        PreparedStatement ps = con.preparedStatement("DELETE FROM unsubscribe WHERE email = ?");
        ps.setString(1, email);
        int result = ps.executeUpdate();
        if (result > 0) {
            System.out.println("You have been successfully removed.");
        } else {
            System.out.println("Invalid email address.");
        }
    }
}