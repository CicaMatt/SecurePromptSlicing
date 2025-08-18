import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginChecker extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginChecker() {
        usernameField = new JTextField(10);
        passwordField = new JPasswordField(10);
        loginButton = new JButton("Login");

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean isValid = check_mod();
                if (isValid) {
                    JOptionPane.showMessageDialog(LoginChecker.this, "Login successful!");
                } else {
                    JOptionPane.showMessageDialog(LoginChecker.this, "Invalid username or password!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        setLayout(new java.awt.FlowLayout());
        add(usernameField);
        add(passwordField);
        add(loginButton);

        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        // Example credentials for demonstration
        if ("admin".equals(username) && "password123".equals(password)) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        new LoginChecker();
    }
}