import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailUpdatePage {
    private JFrame frame;
    private JTextField currentEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton updateButton;
    private JLabel messageLabel;

    public EmailUpdatePage() {
        frame = new JFrame("Update Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(350, 250);
        frame.setLayout(new GridLayout(6, 1));

        JLabel currentEmailLabel = new JLabel("Current Email:");
        currentEmailField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        updateButton = new JButton("Update");
        messageLabel = new JLabel("", SwingConstants.CENTER);

        frame.add(currentEmailLabel);
        frame.add(currentEmailField);
        frame.add(passwordLabel);
        frame.add(passwordField);
        frame.add(newEmailLabel);
        frame.add(newEmailField);
        frame.add(confirmPasswordLabel);
        frame.add(confirmPasswordField);
        frame.add(updateButton);
        frame.add(messageLabel);

        updateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String currentEmail = currentEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);
                String newEmail = newEmailField.getText();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();
                String confirmPassword = new String(confirmPasswordChars);

                if (currentEmail.isEmpty() || password.isEmpty() || newEmail.isEmpty() || confirmPassword.isEmpty()) {
                    messageLabel.setForeground(Color.RED);
                    messageLabel.setText("All fields are required.");
                } else if (!password.equals(confirmPassword)) {
                    messageLabel.setForeground(Color.RED);
                    messageLabel.setText("Passwords do not match.");
                } else if (currentEmail.equals(newEmail)) {
                    messageLabel.setForeground(Color.RED);
                    messageLabel.setText("New email must be different from the current email.");
                } else {
                    // Here you would typically check the database for the correct password
                    // and update the email. For simplicity, we assume the operation is successful.
                    messageLabel.setForeground(Color.GREEN);
                    messageLabel.setText("Email updated successfully!");
                }
            }
        });

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new EmailUpdatePage();
    }
}