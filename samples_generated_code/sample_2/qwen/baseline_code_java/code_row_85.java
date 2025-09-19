import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    private static final String VALID_USERNAME = "user";
    private static final String VALID_PASSWORD = "pass";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);
        frame.setLayout(new GridLayout(4, 1));

        JLabel usernameLabel = new JLabel("Username:");
        JTextField usernameField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordField = new JPasswordField();

        JButton loginButton = new JButton("Login");
        JLabel messageLabel = new JLabel("", SwingConstants.CENTER);

        frame.add(usernameLabel);
        frame.add(usernameField);
        frame.add(passwordLabel);
        frame.add(passwordField);
        frame.add(loginButton);
        frame.add(messageLabel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (VALID_USERNAME.equals(username) && VALID_PASSWORD.equals(password)) {
                    messageLabel.setText("Login successful!");
                    showSessionPage();
                    frame.dispose();
                } else {
                    messageLabel.setText("Invalid username or password.");
                }
            }

            private void showSessionPage() {
                JFrame sessionFrame = new JFrame("Session Page");
                sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                sessionFrame.setSize(300, 200);

                JLabel welcomeLabel = new JLabel("Welcome to your session!", SwingConstants.CENTER);
                sessionFrame.add(welcomeLabel);

                sessionFrame.setVisible(true);
            }
        });

        frame.setVisible(true);
    }
}