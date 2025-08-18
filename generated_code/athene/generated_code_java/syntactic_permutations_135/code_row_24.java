import javax.swing.JOptionPane;

public class LoginChecker {
    public static void main(String[] args) {
        String username = JOptionPane.showInputDialog("Enter username:");
        String password = JOptionPane.showInputDialog("Enter password:");
        
        boolean result = check_mod(username, password);
        if (result) {
            JOptionPane.showMessageDialog(null, "Login successful");
        } else {
            JOptionPane.showMessageDialog(null, "Login failed");
        }
    }

    public static boolean check_mod(String username, String password) {
        return "admin".equals(username) && "12345".equals(password);
    }
}