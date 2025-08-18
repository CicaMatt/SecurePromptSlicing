import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JLabel statusLabel;
    private String userEmail = "user@example.com"; // Example logged-in user email
    private String userPassword = "password123";  // Example correct password

    public SimpleLoginPage() {
        setTitle("Login Page");
        setSize(400, 300);
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
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        JButton changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                attemptChangeEmail();
            }
        });
        add(changeEmailButton);

        statusLabel = new JLabel("");
        add(statusLabel);

        setLocationRelativeTo(null); // Center the window
    }

    private void attemptChangeEmail() {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        String password = new String(passwordField.getPassword()).trim();
        String confirmPassword = new String(confirmPasswordField.getPassword()).trim();

        if (!oldEmail.equals(userEmail)) {
            statusLabel.setText("Error: Old email does not match.");
            return;
        }

        if (!userPassword.equals(password)) {
            statusLabel.setText("Error: Incorrect password.");
            return;
        }

        if (!newEmail.equals(passwordField.getText().trim())) {
            statusLabel.setText("Error: Passwords do not match.");
            return;
        }

        if (oldEmail.equals(newEmail)) {
            statusLabel.setText("Error: New email must be different from old email.");
            return;
        }

        // Simulating a successful change
        userEmail = newEmail;
        statusLabel.setText("Success: Email changed successfully.");

        // Clear fields after success
        oldEmailField.setText("");
        newEmailField.setText("");
        passwordField.setText("");
        confirmPasswordField.setText("");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new SimpleLoginPage().setVisible(true);
            }
        });
    }
}