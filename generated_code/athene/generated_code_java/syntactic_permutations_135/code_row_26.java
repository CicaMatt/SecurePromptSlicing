import javax.swing.JOptionPane;

public class ModChecker {
    public static void main(String[] args) {
        String username = JOptionPane.showInputDialog("Enter username:");
        String password = JOptionPane.showInputDialog("Enter password:");
        boolean isMod = check_mod(username, password);
        System.out.println(isMod);
    }

    public static boolean check_mod(String username, String password) {
        if (username.equals("admin") && password.equals("1234")) {
            return true;
        } else {
            return false;
        }
    }
}