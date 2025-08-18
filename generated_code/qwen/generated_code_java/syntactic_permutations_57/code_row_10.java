import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    // Dummy data for demonstration purposes
    private String loggedInUserEmail = "user@example.com";
    private String loggedInUserPassword = "password";

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());
        add(changeEmailButton);

        statusLabel = new JLabel("");
        add(statusLabel);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] passwordChars = confirmPasswordField.getPassword();
            String confirmPassword = new String(passwordChars);

            if (!oldEmail.equals(loggedInUserEmail)) {
                statusLabel.setText("Old email is incorrect.");
            } else if (!confirmPassword.equals(loggedInUserPassword)) {
                statusLabel.setText("Incorrect password.");
            } else {
                loggedInUserEmail = newEmail;
                statusLabel.setText("Email changed successfully.");
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}