import javax.swing.JOptionPane;

public class LoginChecker {
    public static void main(String[] args) {
        String username = JOptionPane.showInputDialog("Enter Username:");
        String password = JOptionPane.showInputDialog("Enter Password:");
        
        if (checkMod(username, password)) {
            JOptionPane.showMessageDialog(null, "Login Successful!");
        } else {
            JOptionPane.showMessageDialog(null, "Invalid Username or Password.");
        }
    }

    public static boolean checkMod(String username, String password) {
        if ("admin".equals(username) && "123456".equals(password)) {
            return true;
        }
        return false;
    }
}