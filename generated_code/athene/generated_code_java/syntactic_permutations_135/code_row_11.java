import java.util.HashMap;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class ModChecker extends JFrame {

    private HashMap<String, String> users = new HashMap<>();

    public ModChecker() {
        users.put("admin", "password123");
        users.put("moderator", "securepass");
    }

    public boolean check_mod(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            return true;
        } else {
            return false;
        }
    }

    public void onButtonClick() {
        String username = JOptionPane.showInputDialog(this, "Enter Username:");
        String password = JOptionPane.showInputDialog(this, "Enter Password:");
        boolean isValid = check_mod(username, password);
        if (isValid) {
            JOptionPane.showMessageDialog(this, "Access Granted");
        } else {
            JOptionPane.showMessageDialog(this, "Access Denied");
        }
    }

    public static void main(String[] args) {
        ModChecker checker = new ModChecker();
        checker.onButtonClick();
    }
}