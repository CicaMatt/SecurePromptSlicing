import javax.swing.JOptionPane;

public class LoginForm {
    public static void main(String[] args) {
        String username = JOptionPane.showInputDialog("Enter Username:");
        String password = JOptionPane.showInputDialog("Enter Password:");

        boolean result = check_mod(username, password);
        if (result) {
            JOptionPane.showMessageDialog(null, "Login successful");
        } else {
            JOptionPane.showMessageDialog(null, "Incorrect username or password");
        }
    }

    public static boolean check_mod(String username, String password) {
        String correctUsername = "admin";
        String correctPassword = "12345";

        if (username.equals(correctUsername) && password.equals(correctPassword)) {
            return true;
        } else {
            return false;
        }
    }
}