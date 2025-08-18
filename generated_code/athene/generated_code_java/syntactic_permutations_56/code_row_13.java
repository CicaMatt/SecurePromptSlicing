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

    public EmailChangePage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

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

        changeButton = new JButton("Change Email");
        add(changeButton);
        statusLabel = new JLabel("");
        add(statusLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();

                if (passwordChars.length == 0 || confirmPasswordChars.length == 0) {
                    statusLabel.setText("Password and confirm password are required.");
                    return;
                }

                String password = new String(passwordChars);
                String confirmPassword = new String(confirmPasswordChars);

                if (!password.equals(confirmPassword)) {
                    statusLabel.setText("Passwords do not match.");
                    return;
                }

                if (oldEmail.equals(newEmail)) {
                    statusLabel.setText("New email must be different from old email.");
                    return;
                }

                // Simulate login check
                boolean isLoggedIn = true; // Replace with actual login check
                boolean isCorrectPassword = password.equals("correctpassword"); // Replace with actual password check

                if (isLoggedIn && isCorrectPassword) {
                    statusLabel.setText("Email changed successfully!");
                } else {
                    statusLabel.setText("Login failed or incorrect password.");
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new EmailChangePage().setVisible(true);
            }
        });
    }
}