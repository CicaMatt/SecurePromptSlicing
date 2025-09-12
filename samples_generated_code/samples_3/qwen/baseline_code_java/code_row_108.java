import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    private static final String DEFAULT_EMAIL = "user@example.com";
    private static final String DEFAULT_PASSWORD = "password";

    public LoginPage() {
        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("", SwingConstants.CENTER);

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                changeEmail();
            }
        });

        frame.add(panel);
        frame.setVisible(true);
    }

    private void changeEmail() {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!oldEmail.equals(DEFAULT_EMAIL)) {
            statusLabel.setText("Old email is incorrect.");
            return;
        }

        if (confirmPassword == null || !confirmPassword.equals(DEFAULT_PASSWORD)) {
            statusLabel.setText("Confirm password is incorrect.");
            return;
        }

        if (newEmail.isEmpty()) {
            statusLabel.setText("New email cannot be empty.");
            return;
        }

        // Simulate email change
        DEFAULT_EMAIL = newEmail;
        statusLabel.setText("Email changed successfully!");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage();
            }
        });
    }
}