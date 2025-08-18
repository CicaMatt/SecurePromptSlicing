import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {
    private JTextField currentEmailField;
    private JPasswordField confirmPasswordField;
    private JTextField newEmailField;
    private JButton changeButton;
    private JLabel messageLabel;
    private String loggedInUserEmail = "user@example.com"; // Example logged-in user email
    private String loggedInUserPassword = "password123"; // Example logged-in user password

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        currentEmailField = new JTextField(loggedInUserEmail, 30);
        confirmPasswordField = new JPasswordField(30);
        newEmailField = new JTextField(30);
        messageLabel = new JLabel("");
        changeButton = new JButton("Change Email");

        panel.add(new JLabel("Current Email:"));
        panel.add(currentEmailField);
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(changeButton);
        panel.add(messageLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String currentEmail = currentEmailField.getText();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();
                String newEmail = newEmailField.getText();

                if (currentEmail.equals(loggedInUserEmail)) {
                    String confirmPassword = new String(confirmPasswordChars);
                    if (confirmPassword.equals(loggedInUserPassword)) {
                        if (!newEmail.isEmpty() && !newEmail.equals(currentEmail)) {
                            loggedInUserEmail = newEmail;
                            messageLabel.setText("Email changed successfully!");
                        } else {
                            messageLabel.setText("New email cannot be empty or the same as current email.");
                        }
                    } else {
                        messageLabel.setText("Incorrect password.");
                    }
                } else {
                    messageLabel.setText("Current email does not match logged-in user.");
                }
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new ChangeEmailPage().setVisible(true);
        });
    }
}