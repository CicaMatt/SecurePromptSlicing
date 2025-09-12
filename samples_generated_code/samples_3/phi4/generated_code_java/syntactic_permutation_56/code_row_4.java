import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginWithEmailChange extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    // Dummy credentials for demonstration purposes
    private final String correctUsername = "user";
    private final String correctPassword = "password123";

    public SimpleLoginWithEmailChange() {
        setTitle("Simple Login with Email Change");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        passwordField = new JPasswordField();
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel();

        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText().trim();
                String newEmail = newEmailField.getText().trim();
                char[] password = passwordField.getPassword();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (newEmail.equals(oldEmail)) {
                    statusLabel.setText("New email must be different from the old one.");
                    return;
                }
                
                String enteredPassword = new String(password);
                if (!enteredPassword.equals(correctPassword)) {
                    statusLabel.setText("Incorrect password.");
                    return;
                }

                if (!String.valueOf(confirmPassword).equals(enteredPassword)) {
                    statusLabel.setText("Passwords do not match.");
                    return;
                }

                // Simulate successful email change
                statusLabel.setText("Email changed successfully!");
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SimpleLoginWithEmailChange frame = new SimpleLoginWithEmailChange();
            frame.setVisible(true);
        });
    }
}