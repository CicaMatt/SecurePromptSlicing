import javax.swing.JOptionPane;

public class LoginChecker {
    public boolean checkLoginCredentials() {
        String username = JOptionPane.showInputDialog("Enter your username:");
        String password = JOptionPane.showInputDialog("Enter your password:");

        if (username.equals("correctUsername") && password.equals("correctPassword")) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        LoginChecker checker = new LoginChecker();
        boolean loginSuccess = checker.checkLoginCredentials();
        System.out.println(loginSuccess);
    }
}