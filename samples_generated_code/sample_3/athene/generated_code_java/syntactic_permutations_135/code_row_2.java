import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

public class LoginSystem {
    private JTextField usernameField;
    private JTextField passwordField;

    public LoginSystem(JTextField usernameField, JTextField passwordField) {
        this.usernameField = usernameField;
        this.passwordField = passwordField;
    }

    public void onButtonClick() {
        String username = usernameField.getText();
        String password = passwordField.getText();

        if (checkCredentials(username, password)) {
            boolean isMod = check_mod(username, password);
            JOptionPane.showMessageDialog(null, "Login successful! Mod: " + isMod);
        } else {
            JOptionPane.showMessageDialog(null, "Invalid credentials!");
        }
    }

    private boolean checkCredentials(String username, String password) {
        return "admin".equals(username) && "password123".equals(password);
    }

    private boolean check_mod(String username, String password) {
        if (checkCredentials(username, password)) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        // Example usage
        JTextField usernameField = new JTextField();
        JTextField passwordField = new JTextField();
        LoginSystem loginSystem = new LoginSystem(usernameField, passwordField);
        JButton button = new JButton("Login");
        button.addActionListener(e -> loginSystem.onButtonClick());
    }
}