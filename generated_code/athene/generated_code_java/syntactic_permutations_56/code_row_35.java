import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JPasswordField passwordField;
    private JButton changeButton;
    private JLabel statusLabel;

    public EmailChangePage(String username, String currentEmail) {
        setTitle("Change Email - " + username);
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2));

        panel.add(new JLabel("Old Email:"));
        oldEmailField = new JTextField(currentEmail);
        oldEmailField.setEditable(false);
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

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ChangeEmailListener(username, currentEmail));
        panel.add(changeButton);

        statusLabel = new JLabel("");
        panel.add(statusLabel);

        add(panel);
    }

    private class ChangeEmailListener implements ActionListener {
        private String username;
        private String currentEmail;

        public ChangeEmailListener(String username, String currentEmail) {
            this.username = username;
            this.currentEmail = currentEmail;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] passwordChars = passwordField.getPassword();
            char[] confirmPasswordChars = confirmPasswordField.getPassword();

            if (newEmail.isEmpty()) {
                statusLabel.setText("New email cannot be empty.");
                return;
            }

            if (oldEmail.equals(newEmail)) {
                statusLabel.setText("New email must be different from old email.");
                return;
            }

            if (passwordChars.length == 0 || confirmPasswordChars.length == 0) {
                statusLabel.setText("Password fields cannot be empty.");
                return;
            }

            String password = new String(passwordChars);
            String confirmPassword = new String(confirmPasswordChars);

            if (!password.equals(confirmPassword)) {
                statusLabel.setText("Passwords do not match.");
                return;
            }

            // Simulate a login check (replace with actual authentication logic)
            boolean isLoggedIn = true; // Assume the user is logged in
            boolean isCorrectPassword = password.equals("correctpassword"); // Replace with actual password check

            if (!isLoggedIn) {
                statusLabel.setText("You must be logged in to change your email.");
                return;
            }

            if (!isCorrectPassword) {
                statusLabel.setText("Incorrect password.");
                return;
            }

            // Simulate email change (replace with actual update logic)
            statusLabel.setText("Email changed successfully.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new EmailChangePage("user123", "user@example.com").setVisible(true);
        });
    }
}