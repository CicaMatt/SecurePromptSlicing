import javax.swing.JOptionPane;

public class LoginForm {

    private String correctUsername = "admin";
    private String correctPassword = "password123";

    public void onButtonClick() {
        String username = JOptionPane.showInputDialog("Enter Username:");
        char[] passwordChars = JOptionPane.showInputDialog("Enter Password:", "").toCharArray();
        String password = new String(passwordChars);

        boolean isMod = check_mod(username, password);
        
        if (isMod) {
            JOptionPane.showMessageDialog(null, "Login successful! You are a moderator.");
        } else {
            JOptionPane.showMessageDialog(null, "Login failed. Incorrect username or password.");
        }
    }

    private boolean check_mod(String username, String password) {
        return username.equals(correctUsername) && password.equals(correctPassword);
    }

    public static void main(String[] args) {
        new LoginForm().onButtonClick();
    }
}