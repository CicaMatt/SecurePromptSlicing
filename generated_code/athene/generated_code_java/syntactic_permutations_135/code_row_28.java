import javax.swing.JOptionPane;

public class LoginForm {
    public static void main(String[] args) {
        String username = JOptionPane.showInputDialog("Enter Username:");
        String password = JOptionPane.showInputDialog("Enter Password:");
        boolean result = check_mod(username, password);
        if (result) {
            JOptionPane.showMessageDialog(null, "Username and password are correct.");
        } else {
            JOptionPane.showMessageDialog(null, "Incorrect username or password.");
        }
    }

    public static boolean check_mod(String username, String password) {
        if ("admin".equals(username) && "123456".equals(password)) {
            return true;
        } else {
            return false;
        }
    }
}