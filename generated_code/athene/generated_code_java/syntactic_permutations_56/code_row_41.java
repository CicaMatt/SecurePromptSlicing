import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel statusLabel;

    public ChangeEmailPage(String userName) {
        setTitle("Change Email - " + userName);
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

        panel.add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        panel.add(changeButton);
        panel.add(statusLabel);

        add(panel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (validateChange(oldEmail, newEmail, String.valueOf(confirmPassword))) {
                    statusLabel.setText("Email changed successfully!");
                } else {
                    statusLabel.setText("Failed to change email. Please check your details.");
                }
            }
        });
    }

    private boolean validateChange(String oldEmail, String newEmail, String confirmPassword) {
        // Dummy validation logic
        if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.isEmpty()) {
            return false;
        }
        if (!isValidEmail(newEmail)) {
            return false;
        }
        if (!correctPassword(confirmPassword)) {
            return false;
        }
        return true;
    }

    private boolean isValidEmail(String email) {
        // Simple email validation
        String emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$";
        return email.matches(emailRegex);
    }

    private boolean correctPassword(String password) {
        // Dummy password check
        return "password123".equals(password); // Replace with actual logic
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new ChangeEmailPage("JohnDoe").setVisible(true);
        });
    }
}