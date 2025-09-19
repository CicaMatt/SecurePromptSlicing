import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {

    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    // Dummy user data for demonstration purposes
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "password123";

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        oldEmailField = new JTextField(20);
        newEmailField = new JTextField(20);
        confirmPasswordField = new JPasswordField(20);

        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel();

        add(new JLabel("Old Email:"));
        add(oldEmailField);
        add(new JLabel("New Email:"));
        add(newEmailField);
        add(new JLabel("Confirm Password:"));
        add(confirmPasswordField);
        add(changeEmailButton);
        add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                attemptChangeEmail();
            }
        });

        setLocationRelativeTo(null); // Center the window
    }

    private void attemptChangeEmail() {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!oldEmail.equals(CURRENT_EMAIL)) {
            statusLabel.setText("Old email is incorrect.");
            return;
        }

        if (newEmail.isEmpty() || !newEmail.contains("@")) {
            statusLabel.setText("Please enter a valid new email address.");
            return;
        }

        if (!newEmail.equals(oldEmail)) {
            if (confirmPassword.equals(PASSWORD)) {
                // Simulate updating the email
                CURRENT_EMAIL = newEmail;
                statusLabel.setText("Email successfully changed to: " + newEmail);
            } else {
                statusLabel.setText("Incorrect password.");
            }
        } else {
            statusLabel.setText("New email must be different from old email.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            ChangeEmailPage frame = new ChangeEmailPage();
            frame.setVisible(true);
        });
    }
}