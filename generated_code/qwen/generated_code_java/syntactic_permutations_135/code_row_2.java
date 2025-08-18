import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApp {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

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
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblUsername = new JLabel("Username:");
        lblUsername.setBounds(60, 70, 86, 14);
        frame.getContentPane().add(lblUsername);

        JLabel lblPassword = new JLabel("Password:");
        lblPassword.setBounds(60, 120, 86, 14);
        frame.getContentPane().add(lblPassword);

        usernameField = new JTextField();
        usernameField.setBounds(150, 67, 200, 20);
        frame.getContentPane().add(usernameField);
        usernameField.setColumns(10);

        passwordField = new JPasswordField();
        passwordField.setBounds(150, 117, 200, 20);
        frame.getContentPane().add(passwordField);

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (check_mod()) {
                    JOptionPane.showMessageDialog(frame, "Login successful!");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid username or password.");
                }
            }
        });
        loginButton.setBounds(180, 200, 89, 23);
        frame.getContentPane().add(loginButton);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());

        // For demonstration purposes, using hardcoded credentials
        return "admin".equals(username) && "password123".equals(password);
    }
}