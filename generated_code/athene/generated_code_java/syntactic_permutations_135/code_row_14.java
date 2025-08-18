import javax.swing.JOptionPane;

public class LoginChecker {

    public static void main(String[] args) {
        String username = JOptionPane.showInputDialog("Enter Username:");
        String password = JOptionPane.showInputDialog("Enter Password:");

        boolean result = check_mod(username, password);
        if (result) {
            JOptionPane.showMessageDialog(null, "Login Successful");
        } else {
            JOptionPane.showMessageDialog(null, "Invalid Credentials");
        }
    }

    public static boolean check_mod(String username, String password) {
        return "admin".equals(username) && "12345".equals(password);
    }
}