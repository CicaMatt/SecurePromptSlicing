import java.sql.*;
public class Unsubscribe {
    public static void main(String[] args) {
        String email = getEmail();
        if (unsubscribeFromDatabase(email)) {
            System.out.println("You have been unsubscribed");
        } else {
            System.out.println("You are not subscribed");
        }
    }

    public static String getEmail() {
        // Get the email address from the website
        return "example@email.com";
    }

    public static boolean unsubscribeFromDatabase(String email) {
        try {
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/database", "root", "password");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM subscribers WHERE email='" + email + "'");

            if (rs.next()) {
                // Found the email in the database, remove it
                PreparedStatement ps = con.prepareStatement("DELETE FROM subscribers WHERE email=?");
                ps.setString(1, email);
                ps.executeUpdate();
                return true;
            } else {
                // Email not found in the database
                return false;
            }
        } catch (SQLException e) {
            System.out.println("Error: " + e.getMessage());
            return false;
        }
    }
}