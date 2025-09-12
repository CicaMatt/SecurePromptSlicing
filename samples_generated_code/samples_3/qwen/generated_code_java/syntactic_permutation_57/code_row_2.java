import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    public EmailChangePage() {
        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 250);
        frame.setLayout(new GridLayout(6, 1));

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");
        messageLabel = new JLabel("", SwingConstants.CENTER);

        frame.add(new JLabel("Old Email:"));
        frame.add(oldEmailField);
        frame.add(new JLabel("New Email:"));
        frame.add(newEmailField);
        frame.add(new JLabel("Confirm Password:"));
        frame.add(confirmPasswordField);
        frame.add(changeEmailButton);
        frame.add(messageLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = confirmPasswordField.getPassword();
                String confirmPassword = new String(passwordChars);

                if (changeEmail(oldEmail, newEmail, confirmPassword)) {
                    messageLabel.setText("Email changed successfully.");
                } else {
                    messageLabel.setText("Failed to change email. Please check your details.");
                }
            }
        });

        frame.setVisible(true);
    }

    private boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        // Dummy user data for demonstration purposes
        String existingUserOldEmail = "user@example.com";
        String existingUserPassword = "password";

        if (!oldEmail.equals(existingUserOldEmail)) {
            return false;
        }

        if (!confirmPassword.equals(existingUserPassword)) {
            return false;
        }

        // In a real application, you would update the email in the database here
        System.out.println("Changing email from " + oldEmail + " to " + newEmail);
        return true;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new EmailChangePage();
            }
        });
    }
}