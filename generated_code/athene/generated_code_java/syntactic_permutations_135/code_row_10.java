import javax.swing.JOptionPane;

public class LoginChecker {

    public static boolean check_mod() {
        String username = JOptionPane.showInputDialog("Enter Username:");
        String password = JOptionPane.showInputDialog("Enter Password:");

        if (username.equals("admin") && password.equals("123456")) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        boolean result = check_mod();
        System.out.println(result);
    }
}