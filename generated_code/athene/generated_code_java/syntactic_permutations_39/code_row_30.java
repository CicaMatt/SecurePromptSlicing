import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JLabel messageLabel;

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                LoginPage window = new LoginPage();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    public LoginPage() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame("Login Page");
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setBounds(58, 69, 61, 16);
        frame.getContentPane().add(usernameLabel);

        usernameField = new JTextField();
        usernameField.setBounds(123, 66, 130, 22);
        frame.getContentPane().add(usernameField);
        usernameField.setColumns(10);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(58, 97, 61, 16);
        frame.getContentPane().add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setBounds(123, 94, 130, 22);
        frame.getContentPane().add(passwordField);

        JButton loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);
                if (username.equals("admin") && password.equals("password")) {
                    openSessionPage();
                } else {
                    messageLabel.setText("Incorrect username or password.");
                }
            }
        });
        loginButton.setBounds(123, 124, 117, 25);
        frame.getContentPane().add(loginButton);

        messageLabel = new JLabel("");
        messageLabel.setForeground(Color.RED);
        messageLabel.setBounds(123, 150, 300, 16);
        frame.getContentPane().add(messageLabel);
    }

    private void openSessionPage() {
        JFrame sessionFrame = new JFrame("Session Page");
        sessionFrame.setBounds(100, 100, 450, 300);
        sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        sessionFrame.getContentPane().setLayout(null);

        JLabel sessionLabel = new JLabel("Welcome to the Session Page!");
        sessionLabel.setBounds(123, 69, 200, 16);
        sessionFrame.getContentPane().add(sessionLabel);

        JButton logoutButton = new JButton("Logout");
        logoutButton.addActionListener(e -> frame.setVisible(true));
        logoutButton.setBounds(150, 124, 117, 25);
        sessionFrame.getContentPane().add(logoutButton);

        sessionFrame.setVisible(true);
        frame.setVisible(false);
    }
}