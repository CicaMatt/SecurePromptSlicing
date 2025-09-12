import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage {
    private static final String VALID_USERNAME = "admin";
    private static final String VALID_PASSWORD = "password";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel userLabel = new JLabel("User");
        userLabel.setBounds(10, 10, 80, 25);
        panel.add(userLabel);

        JTextField userText = new JTextField(20);
        userText.setBounds(100, 10, 165, 25);
        panel.add(userText);

        JLabel passwordLabel = new JLabel("Password");
        passwordLabel.setBounds(10, 40, 80, 25);
        panel.add(passwordLabel);

        JPasswordField passwordText = new JPasswordField(20);
        passwordText.setBounds(100, 40, 165, 25);
        panel.add(passwordText);

        JButton loginButton = new JButton("login");
        loginButton.setBounds(10, 80, 80, 25);
        panel.add(loginButton);

        JLabel messageLabel = new JLabel("");
        messageLabel.setBounds(10, 120, 300, 25);
        panel.add(messageLabel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = userText.getText();
                char[] passwordArray = passwordText.getPassword();
                String password = new String(passwordArray);

                if (username.equals(VALID_USERNAME) && password.equals(VALID_PASSWORD)) {
                    messageLabel.setText("Login successful!");
                    openSessionPage();
                } else {
                    messageLabel.setText("Invalid username or password.");
                }
            }
        });
    }

    private static void openSessionPage() {
        JFrame sessionFrame = new JFrame("Session Page");
        sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        sessionFrame.setSize(300, 200);

        JPanel panel = new JPanel();
        sessionFrame.add(panel);
        placeComponentsInSessionPanel(panel);

        sessionFrame.setVisible(true);
    }

    private static void placeComponentsInSessionPanel(JPanel panel) {
        panel.setLayout(null);

        JLabel welcomeLabel = new JLabel("Welcome to your session!");
        welcomeLabel.setBounds(10, 40, 280, 25);
        panel.add(welcomeLabel);
    }
}