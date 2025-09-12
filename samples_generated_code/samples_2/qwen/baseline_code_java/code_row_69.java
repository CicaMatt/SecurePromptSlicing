import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmPasswordField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(350, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(6, 2));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        add(passwordField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JTextField();
        add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());
        add(changeEmailButton);

        messageLabel = new JLabel("");
        add(messageLabel);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            String password = new String(passwordField.getPassword());
            String confirmPassword = confirmPasswordField.getText();

            if (!password.equals("correctPassword")) { // Replace with actual password verification logic
                messageLabel.setText("Incorrect password.");
                return;
            }

            if (newEmail.equals(oldEmail)) {
                messageLabel.setText("New email must be different from the old email.");
                return;
            }

            if (!confirmPassword.equals(password)) {
                messageLabel.setText("Passwords do not match.");
                return;
            }

            // Simulate email change
            messageLabel.setText("Email changed successfully.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage frame = new LoginPage();
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });
    }
}