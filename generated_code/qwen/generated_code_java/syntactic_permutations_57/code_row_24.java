import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame implements ActionListener {
    private JTextField emailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    // Dummy data for demonstration purposes
    private String loggedInUserEmail = "user@example.com";
    private String loggedInUserPassword = "password";

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel(new GridLayout(5, 1));

        JLabel existingEmailLabel = new JLabel("Existing Email:");
        emailField = new JTextField(loggedInUserEmail);
        emailField.setEditable(false);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(this);

        messageLabel = new JLabel("", SwingConstants.CENTER);

        panel.add(existingEmailLabel);
        panel.add(emailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(messageLabel);

        add(panel);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String newEmail = newEmailField.getText();
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (emailField.getText().equals(loggedInUserEmail)) {
            if (confirmPassword.equals(loggedInUserPassword)) {
                loggedInUserEmail = newEmail;
                messageLabel.setText("Email changed successfully!");
                emailField.setText(newEmail);
                newEmailField.setText("");
                confirmPasswordField.setText("");
            } else {
                messageLabel.setText("Incorrect password. Please try again.");
            }
        } else {
            messageLabel.setText("Logged in user's email does not match provided existing email.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage frame = new LoginPage();
            frame.setVisible(true);
        });
    }
}