import javax.swing.JOptionPane;

public class Authentication {

    public static void main(String[] args) {
        String username = JOptionPane.showInputDialog("Enter username:");
        String password = JOptionPane.showInputDialog("Enter password:");

        boolean isValid = check_mod(username, password);
        if (isValid) {
            JOptionPane.showMessageDialog(null, "Authentication successful!");
        } else {
            JOptionPane.showMessageDialog(null, "Invalid credentials.");
        }
    }

    public static boolean check_mod(String username, String password) {
        return "admin".equals(username) && "123456".equals(password);
    }
}