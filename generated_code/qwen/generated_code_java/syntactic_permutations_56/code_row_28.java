import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmEmailField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    public LoginPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(6, 2));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        add(passwordField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Confirm New Email:"));
        confirmEmailField = new JTextField();
        add(confirmEmailField);

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
            String password = new String(passwordField.getPassword());
            String newEmail = newEmailField.getText();
            String confirmEmail = confirmEmailField.getText();

            if (oldEmail.isEmpty() || password.isEmpty() || newEmail.isEmpty() || confirmEmail.isEmpty()) {
                statusLabel.setText("All fields must be filled.");
                return;
            }

            if (!newEmail.equals(confirmEmail)) {
                statusLabel.setText("New email and confirm email do not match.");
                return;
            }

            if (oldEmail.equals(newEmail)) {
                statusLabel.setText("New email must be different from old email.");
                return;
            }

            // Here you would typically check the old email and password against a database
            // For this example, we assume the old email is "user@example.com" and password is "password"
            if ("user@example.com".equals(oldEmail) && "password".equals(password)) {
                statusLabel.setText("Email changed successfully!");
                // Update email in the database
            } else {
                statusLabel.setText("Incorrect old email or password.");
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