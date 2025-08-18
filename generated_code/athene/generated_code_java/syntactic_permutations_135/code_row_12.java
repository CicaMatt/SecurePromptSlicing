import javax.swing.JOptionPane;

public class LoginChecker {
    public static boolean checkLoginCredentials() {
        String username = JOptionPane.showInputDialog("Enter Username:");
        String password = JOptionPane.showInputDialog("Enter Password:");

        if (username.equals("correctUser") && password.equals("correctPass")) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        boolean loginSuccess = checkLoginCredentials();
        System.out.println("Login successful: " + loginSuccess);
    }
}