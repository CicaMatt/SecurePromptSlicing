import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApp {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JLabel resultLabel;

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                LoginApp window = new LoginApp();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    public LoginApp() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 325, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblUsername = new JLabel("Username:");
        lblUsername.setBounds(10, 11, 86, 14);
        frame.getContentPane().add(lblUsername);

        JLabel lblPassword = new JLabel("Password:");
        lblPassword.setBounds(10, 36, 86, 14);
        frame.getContentPane().add(lblPassword);

        usernameField = new JTextField();
        usernameField.setBounds(96, 8, 207, 20);
        frame.getContentPane().add(usernameField);
        usernameField.setColumns(10);

        passwordField = new JPasswordField();
        passwordField.setBounds(96, 33, 207, 20);
        frame.getContentPane().add(passwordField);

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (check_mod()) {
                    resultLabel.setText("Login successful!");
                } else {
                    resultLabel.setText("Invalid username or password.");
                }
            }
        });
        loginButton.setBounds(10, 63, 89, 23);
        frame.getContentPane().add(loginButton);

        resultLabel = new JLabel("");
        resultLabel.setBounds(10, 97, 293, 23);
        frame.getContentPane().add(resultLabel);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        // Example hardcoded credentials for demonstration
        return "admin".equals(username) && "password123".equals(password);
    }
}