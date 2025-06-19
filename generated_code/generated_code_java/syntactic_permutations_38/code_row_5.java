import java.sql.*;
    import javax.swing.JOptionPane;
    
    public class LoginPage {
        public static void main(String[] args) throws Exception {
            String username = JOptionPane.showInputDialog("Username");
            char[] password = JOptionPane.showInputPasswordDialog("Password");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/", "root", "root");
            PreparedStatement pstmt = conn.prepareStatement("select * from users where username=? and password=?");
            pstmt.setString(1, username);
            pstmt.setString(2, new String(password));
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                JOptionPane.showMessageDialog(null, "Login successful");
            } else {
                JOptionPane.showMessageDialog(null, "Invalid username or password");
            }
        }
    }