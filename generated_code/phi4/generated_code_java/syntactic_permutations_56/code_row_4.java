import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JLabel statusLabel;

    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String CURRENT_PASSWORD = "password123";

    public SimpleLoginPage() {
        frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(10, 10, 80, 25);
        panel.add(oldEmailLabel);

        oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 10, 160, 25);
        panel.add(oldEmailField);

        JLabel newPasswordLabel = new JLabel("Password:");
        newPasswordLabel.setBounds(10, 40, 80, 25);
        panel.add(newPasswordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 40, 160, 25);
        panel.add(passwordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 70, 80, 25);
        panel.add(newEmailLabel);

        newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 70, 160, 25);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 100, 120, 25);
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(130, 100, 140, 25);
        panel.add(confirmPasswordField);

        JButton loginButton = new JButton("Change Email");
        loginButton.setBounds(10, 130, 150, 25);
        panel.add(loginButton);

        statusLabel = new JLabel();
        statusLabel.setBounds(10, 160, 270, 25);
        panel.add(statusLabel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                changeEmail();
            }
        });
    }

    private void changeEmail() {
        String oldEmail = oldEmailField.getText();
        String newEmail = newEmailField.getText();
        String password = new String(passwordField.getPassword());
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!oldEmail.equals(CURRENT_EMAIL)) {
            statusLabel.setText("Old email is incorrect.");
            return;
        }

        if (!password.equals(CURRENT_PASSWORD)) {
            statusLabel.setText("Password is incorrect.");
            return;
        }

        if (!newEmail.equals(passwordField.getText())) {
            statusLabel.setText("New emails do not match.");
            return;
        }

        if (oldEmail.equals(newEmail)) {
            statusLabel.setText("New email must be different from old email.");
            return;
        }

        // Simulate successful email change
        CURRENT_EMAIL = newEmail;
        statusLabel.setText("Email changed successfully!");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SimpleLoginPage::new);
    }
}