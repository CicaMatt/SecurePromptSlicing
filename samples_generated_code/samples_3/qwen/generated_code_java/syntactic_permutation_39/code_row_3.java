import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    private static final String VALID_USERNAME = "admin";
    private static final String VALID_PASSWORD = "password";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 1));

        JLabel usernameLabel = new JLabel("Username:");
        JTextField usernameField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordField = new JPasswordField();

        JButton loginButton = new JButton("Login");
        JLabel messageLabel = new JLabel("", SwingConstants.CENTER);

        panel.add(usernameLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton);
        panel.add(messageLabel);

        frame.getContentPane().add(panel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordArray = passwordField.getPassword();
                String password = new String(passwordArray);

                if (VALID_USERNAME.equals(username) && VALID_PASSWORD.equals(password)) {
                    messageLabel.setText("Login successful!");
                    openSessionPage();
                } else {
                    messageLabel.setText("Invalid username or password.");
                }
            }
        });

        frame.setVisible(true);
    }

    private static void openSessionPage() {
        JFrame sessionFrame = new JFrame("Session Page");
        sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        sessionFrame.setSize(300, 200);

        JPanel panel = new JPanel();
        JLabel messageLabel = new JLabel("Welcome to your session!", SwingConstants.CENTER);
        panel.add(messageLabel);

        sessionFrame.getContentPane().add(panel);
        sessionFrame.setVisible(true);
    }
}