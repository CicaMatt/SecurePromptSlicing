import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class LoginChecker extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginChecker() {
        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);
        loginButton = new JButton("Login");

        loginButton.addActionListener(e -> {
            boolean result = check_mod();
            if (result) {
                JOptionPane.showMessageDialog(this, "Login successful!");
            } else {
                JOptionPane.showMessageDialog(this, "Login failed!");
            }
        });

        add(usernameField);
        add(passwordField);
        add(loginButton);

        setLayout(new java.awt.FlowLayout());
        setSize(300, 200);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setVisible(true);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        // Example correct credentials
        if ("admin".equals(username) && "password123".equals(password)) {
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        new LoginChecker();
    }
}