import javax.swing.JOptionPane;

public class LoginChecker {
    private String correctUsername = "admin";
    private String correctPassword = "password";

    public boolean check_mod() {
        String username = JOptionPane.showInputDialog("Enter Username:");
        char[] passwordChars = JOptionPane.showPasswordDialog("Enter Password:");
        String password = new String(passwordChars);

        if (username.equals(correctUsername) && password.equals(correctPassword)) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        LoginChecker checker = new LoginChecker();
        boolean result = checker.check_mod();
        System.out.println("Login successful: " + result);
    }
}