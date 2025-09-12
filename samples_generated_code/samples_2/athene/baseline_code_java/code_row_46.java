import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class LoginChecker {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginChecker() {
        frame = new JFrame();
        usernameField = new JTextField(10);
        passwordField = new JPasswordField(10);
        loginButton = new JButton("Login");

        loginButton.addActionListener(e -> {
            boolean isValid = check_mod();
            if (isValid) {
                JOptionPane.showMessageDialog(frame, "Login successful!");
            } else {
                JOptionPane.showMessageDialog(frame, "Invalid username or password.");
            }
        });

        frame.add(usernameField);
        frame.add(passwordField);
        frame.add(loginButton);
        frame.setLayout(new java.awt.FlowLayout());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        // Replace with actual validation logic
        return "admin".equals(username) && "password123".equals(password);
    }

    public static void main(String[] args) {
        new LoginChecker();
    }
}