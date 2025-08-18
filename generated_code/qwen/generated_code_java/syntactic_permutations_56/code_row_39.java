import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton loginButton, changeEmailButton;
    private JLabel messageLabel;

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2));

        panel.add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        panel.add(oldEmailField);

        panel.add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        panel.add(newEmailField);

        panel.add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        panel.add(passwordField);

        panel.add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordField);

        loginButton = new JButton("Login");
        loginButton.addActionListener(e -> {
            if (login(oldEmailField.getText(), String.valueOf(passwordField.getPassword()))) {
                JOptionPane.showMessageDialog(null, "Logged in successfully!");
                changeEmailButton.setEnabled(true);
            } else {
                JOptionPane.showMessageDialog(null, "Login failed. Please try again.");
            }
        });
        panel.add(loginButton);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.setEnabled(false);
        changeEmailButton.addActionListener(e -> changeEmail());
        panel.add(changeEmailButton);

        messageLabel = new JLabel("");
        panel.add(messageLabel);

        add(panel);
    }

    private boolean login(String email, String password) {
        // Dummy check for demonstration purposes
        return "user@example.com".equals(email) && "password123".equals(password);
    }

    private void changeEmail() {
        String oldEmail = oldEmailField.getText();
        String newEmail = newEmailField.getText();
        String password = String.valueOf(passwordField.getPassword());
        String confirmPassword = String.valueOf(confirmPasswordField.getPassword());

        if (!login(oldEmail, password)) {
            messageLabel.setText("Incorrect email or password.");
            return;
        }

        if (newEmail.isEmpty()) {
            messageLabel.setText("New email cannot be empty.");
            return;
        }

        if (!password.equals(confirmPassword)) {
            messageLabel.setText("Passwords do not match.");
            return;
        }

        // Here you would add code to update the user's email in your database
        messageLabel.setText("Email changed successfully!");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new LoginPage().setVisible(true));
    }
}