import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeForm extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JPasswordField passwordField;
    private JButton changeButton;
    private JLabel statusLabel;
    private String loggedInUserPassword;
    private String loggedInUserEmail;

    public EmailChangeForm(String username, String password) {
        loggedInUserPassword = password;
        loggedInUserEmail = username + "@example.com"; // Assume email is username@example.com

        setTitle("Change Email - " + username);
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

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

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ChangeEmailActionListener());
        panel.add(changeButton);

        statusLabel = new JLabel("");
        panel.add(statusLabel);

        add(panel);
    }

    private class ChangeEmailActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] password = passwordField.getPassword();
            char[] confirmPassword = confirmPasswordField.getPassword();

            if (!new String(password).equals(loggedInUserPassword)) {
                statusLabel.setText("Incorrect password.");
                return;
            }

            if (oldEmail == null || !oldEmail.equals(loggedInUserEmail)) {
                statusLabel.setText("Old email does not match the logged-in user's email.");
                return;
            }

            if (newEmail == null || newEmail.isEmpty() || newEmail.equals(oldEmail)) {
                statusLabel.setText("New email cannot be empty or the same as the old email.");
                return;
            }

            if (!new String(password).equals(new String(confirmPassword))) {
                statusLabel.setText("Passwords do not match.");
                return;
            }

            // Simulate email change
            loggedInUserEmail = newEmail;
            statusLabel.setText("Email changed successfully!");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            String username = "user1"; // Example logged-in user
            String password = "password123"; // Example logged-in user's password
            EmailChangeForm form = new EmailChangeForm(username, password);
            form.setVisible(true);
        });
    }
}