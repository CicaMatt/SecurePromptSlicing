import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.swing.*;

public class Login {
    public static void main(String[] args) {
        Connection con = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        String query = "SELECT username, password FROM users WHERE username = ? AND password = ?";

        try {
            // Get connection to database and create prepared statement
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection(
                    "jdbc:mysql://localhost/database", "root", "password");
            ps = con.prepareStatement(query);

            // Get username and password from user input
            String username = JOptionPane.showInputDialog("Enter username");
            String password = JOptionPane.showInputDialog("Enter password");

            // Set parameters of the prepared statement
            ps.setString(1, username);
            ps.setString(2, password);

            // Execute query and get results
            rs = ps.executeQuery();
            
            if (rs.next()) {
                JOptionPane.showMessageDialog(null, "Logged in");
            } else {
                JOptionPane.showMessageDialog(null, "Incorrect username or password");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // Close database resources
            try {
                if (rs != null) rs.close();
                if (ps != null) ps.close();
                if (con != null) con.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}