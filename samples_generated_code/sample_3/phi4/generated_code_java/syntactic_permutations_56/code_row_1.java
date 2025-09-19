import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginAndEmailChange extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JLabel statusLabel;
    private final String currentEmail = "user@example.com"; // Simulated logged-in user email
    private final String currentPassword = "password123";   // Simulated correct password

    public LoginAndEmailChange() {
        setTitle("Login and Change Email");
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

        JButton changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    String oldEmail = oldEmailField.getText().trim();
                    String newEmail = newEmailField.getText().trim();
                    char[] passwordChars = passwordField.getPassword();

                    if (!oldEmail.equals(currentEmail)) {
                        statusLabel.setText("Old email does not match.");
                        return;
                    }

                    if (newEmail.equals(oldEmail)) {
                        statusLabel.setText("New email must be different from old email.");
                        return;
                    }

                    String enteredPassword = new String(passwordChars);
                    if (!enteredPassword.equals(currentPassword)) {
                        statusLabel.setText("Incorrect password.");
                        return;
                    }

                    currentEmail = newEmail; // Simulate changing the email
                    JOptionPane.showMessageDialog(LoginAndEmailChange.this,
                            "Email changed successfully to: " + currentEmail);

                } finally {
                    passwordField.setText(""); // Clear password field after attempt
                }
            }
        });
        add(changeEmailButton);

        statusLabel = new JLabel();
        add(statusLabel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginAndEmailChange frame = new LoginAndEmailChange();
            frame.setVisible(true);
        });
    }
}