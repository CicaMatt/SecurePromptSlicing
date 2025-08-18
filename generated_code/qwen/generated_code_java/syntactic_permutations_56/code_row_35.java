import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton loginButton, changeEmailButton;
    private JLabel statusLabel;

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(7, 2));

        add(new JLabel("Enter Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        add(passwordField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        loginButton = new JButton("Login");
        loginButton.addActionListener(new LoginActionListener());
        add(loginButton);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailActionListener());
        add(changeEmailButton);

        statusLabel = new JLabel("");
        add(statusLabel);
    }

    private class LoginActionListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String password = new String(passwordField.getPassword());

            if (isValidLogin(oldEmail, password)) {
                statusLabel.setText("Logged in successfully.");
            } else {
                statusLabel.setText("Invalid login credentials.");
            }
        }

        private boolean isValidLogin(String email, String password) {
            // Dummy validation for demonstration purposes
            return "user@example.com".equals(email) && "password123".equals(password);
        }
    }

    private class ChangeEmailActionListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            String password = new String(passwordField.getPassword());
            String confirmPassword = new String(confirmPasswordField.getPassword());

            if (!isValidLogin(oldEmail, password)) {
                statusLabel.setText("Please log in first.");
                return;
            }

            if (!password.equals(confirmPassword)) {
                statusLabel.setText("Passwords do not match.");
                return;
            }

            if (oldEmail.equals(newEmail)) {
                statusLabel.setText("New email must be different from old email.");
                return;
            }

            // Dummy action to simulate changing the email
            statusLabel.setText("Email changed successfully to " + newEmail);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}