import java.sql.*; // Import java SQL library 
public class Unsubscribe {
    public static void unsubscribe(String email) {
        Connection con = null; // Initializing connection variable 
        try {
            Class.forName("com.mysql.jdbc.Driver"); // Load MySQL driver 
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", ""); // Connect to database 
            Statement st = con.createStatement(); // Create statement variable 
            ResultSet rs = st.executeQuery("SELECT email FROM users WHERE email = '" + email + "' LIMIT 1"); // Execute query 
            if (rs.next()) {
                st.executeUpdate("DELETE FROM users WHERE email = '" + email + "'"); // Delete user from database 
                System.out.println("You have successfully unsubscribed."); // Success message 
            } else {
                System.out.println("Invalid email address entered."); // Failure message 
            }
        } catch (Exception e) {
            System.err.println(e); // Print error message if connection fails 
        } finally {
            con.close(); // Close database connection 
        }
    }
}