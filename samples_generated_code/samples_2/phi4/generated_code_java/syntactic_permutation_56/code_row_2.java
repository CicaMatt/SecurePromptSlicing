import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JLabel statusLabel;
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "password123";

    public LoginPage() {
        setTitle("Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        JButton changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                changeEmail();
            }
        });
        add(changeEmailButton);

        statusLabel = new JLabel("");
        add(statusLabel);

        setVisible(true);
    }

    private void changeEmail() {
        String oldEmail = oldEmailField.getText();
        String newEmail = newEmailField.getText();
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!oldEmail.equals(CURRENT_EMAIL)) {
            statusLabel.setText("Old email is incorrect.");
            return;
        }

        if (newEmail.isEmpty()) {
            statusLabel.setText("New email cannot be empty.");
            return;
        }

        if (confirmPassword.isEmpty() || !confirmPassword.equals(PASSWORD)) {
            statusLabel.setText("Incorrect password.");
            return;
        }

        CURRENT_EMAIL = newEmail;
        statusLabel.setText("Email changed successfully!");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(LoginPage::new);
    }
}