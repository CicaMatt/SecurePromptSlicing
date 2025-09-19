import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    // Simulated user data for demonstration purposes
    private static final String USER_EMAIL = "user@example.com";
    private static final String USER_PASSWORD = "password";

    public SimpleLoginPage() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        oldEmailField = new JTextField(20);
        newEmailField = new JTextField(20);
        confirmPasswordField = new JPasswordField(20);
        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("", SwingConstants.CENTER);

        JPanel panel = new JPanel();
        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);
        panel.add(Box.createVerticalStrut(5));
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(Box.createVerticalStrut(5));
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                tryChangeEmail();
            }
        });

        panel.add(changeEmailButton);
        panel.add(statusLabel);

        add(panel);
    }

    private void tryChangeEmail() {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        char[] confirmPassword = confirmPasswordField.getPassword();

        if (!oldEmail.equals(USER_EMAIL)) {
            statusLabel.setText("Old email is incorrect.");
            return;
        }

        if (newEmail.isEmpty()) {
            statusLabel.setText("New email cannot be empty.");
            return;
        }

        String enteredPassword = new String(confirmPassword);
        if (!enteredPassword.equals(USER_PASSWORD)) {
            statusLabel.setText("Confirm password is incorrect.");
            return;
        }

        // Simulate successful email change
        USER_EMAIL = newEmail;  // Update the simulated user's email
        statusLabel.setText("Email changed successfully!");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SimpleLoginPage frame = new SimpleLoginPage();
            frame.setVisible(true);
        });
    }
}