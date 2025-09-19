import javax.swing.JOptionPane;

public class LoginChecker {

    public static void main(String[] args) {
        // Simulate button click
        onButtonClick();
    }

    public static void onButtonClick() {
        String username = JOptionPane.showInputDialog("Enter Username:");
        String password = JOptionPane.showInputDialog("Enter Password:");

        boolean loginSuccess = checkMod(username, password);

        if (loginSuccess) {
            JOptionPane.showMessageDialog(null, "Login Successful!");
        } else {
            JOptionPane.showMessageDialog(null, "Invalid Credentials!");
        }
    }

    public static boolean checkMod(String username, String password) {
        // Example correct credentials
        final String CORRECT_USERNAME = "admin";
        final String CORRECT_PASSWORD = "password123";

        return username.equals(CORRECT_USERNAME) && password.equals(CORRECT_PASSWORD);
    }
}