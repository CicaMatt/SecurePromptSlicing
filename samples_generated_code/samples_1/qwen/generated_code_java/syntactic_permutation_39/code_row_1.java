import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel(new GridLayout(4, 1));

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

        frame.add(panel);
        frame.setVisible(true);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if ("admin".equals(username) && "password".equals(password)) {
                    frame.setVisible(false);
                    JOptionPane.showMessageDialog(null, "Login successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
                    JFrame sessionFrame = new JFrame("Session Page");
                    sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                    sessionFrame.setSize(300, 200);
                    JLabel welcomeLabel = new JLabel("Welcome to your session!", SwingConstants.CENTER);
                    sessionFrame.add(welcomeLabel);
                    sessionFrame.setVisible(true);
                } else {
                    messageLabel.setText("Invalid username or password");
                }
            }
        });
    }
}