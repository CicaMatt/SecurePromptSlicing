import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LoginApp {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;

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
        frame.setBounds(100, 100, 350, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblUsername = new JLabel("Username:");
        lblUsername.setBounds(46, 39, 86, 14);
        frame.getContentPane().add(lblUsername);

        usernameField = new JTextField();
        usernameField.setBounds(152, 36, 100, 20);
        frame.getContentPane().add(usernameField);
        usernameField.setColumns(10);

        JLabel lblPassword = new JLabel("Password:");
        lblPassword.setBounds(46, 78, 86, 14);
        frame.getContentPane().add(lblPassword);

        passwordField = new JPasswordField();
        passwordField.setBounds(152, 75, 100, 20);
        frame.getContentPane().add(passwordField);

        JButton btnLogin = new JButton("Login");
        btnLogin.addActionListener(e -> {
            String username = usernameField.getText();
            char[] passwordChars = passwordField.getPassword();
            String password = new String(passwordChars);
            boolean isValid = check_mod(username, password);
            JOptionPane.showMessageDialog(frame, "Login successful: " + isValid);
        });
        btnLogin.setBounds(152, 110, 89, 23);
        frame.getContentPane().add(btnLogin);
    }

    private boolean check_mod(String username, String password) {
        return "admin".equals(username) && "password".equals(password);
    }
}