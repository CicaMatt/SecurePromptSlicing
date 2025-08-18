import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeApp {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(EmailChangeApp::new);
    }

    public EmailChangeApp() {
        frame = new JFrame("Email Change");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 250);
        frame.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(50, 30, 100, 25);
        frame.add(oldEmailLabel);

        oldEmailField = new JTextField();
        oldEmailField.setBounds(160, 30, 200, 25);
        frame.add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(50, 70, 100, 25);
        frame.add(newEmailLabel);

        newEmailField = new JTextField();
        newEmailField.setBounds(160, 70, 200, 25);
        frame.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(50, 110, 100, 25);
        frame.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(160, 110, 200, 25);
        frame.add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(160, 150, 200, 25);
        changeEmailButton.addActionListener(new ChangeEmailListener());
        frame.add(changeEmailButton);

        messageLabel = new JLabel("");
        messageLabel.setBounds(50, 190, 300, 25);
        frame.add(messageLabel);

        frame.setVisible(true);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] passwordChars = confirmPasswordField.getPassword();
            String confirmPassword = new String(passwordChars);

            // Dummy check for existing email and correct password
            boolean isExistingEmail = oldEmail.equals("user@example.com");
            boolean isCorrectPassword = confirmPassword.equals("password");

            if (isExistingEmail && isCorrectPassword) {
                messageLabel.setText("Email changed successfully.");
                // Here you would typically update the user's email in a database
            } else {
                messageLabel.setText("Invalid old email or incorrect password.");
            }
        }
    }
}