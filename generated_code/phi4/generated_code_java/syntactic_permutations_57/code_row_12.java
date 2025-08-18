import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChanger extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel messageLabel;

    public EmailChanger() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        confirmPasswordField = new JPasswordField();
        changeButton = new JButton("Change Email");
        messageLabel = new JLabel("");

        add(createInputPanel("Old Email: ", oldEmailField));
        add(createInputPanel("New Email: ", newEmailField));
        add(createInputPanel("Confirm Password: ", confirmPasswordField));
        add(changeButton);
        add(messageLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                handleEmailChange();
            }
        });
    }

    private JPanel createInputPanel(String label, JComponent component) {
        JPanel panel = new JPanel();
        panel.add(new JLabel(label));
        panel.add(component);
        return panel;
    }

    private void handleEmailChange() {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (oldEmail.isEmpty()) {
            messageLabel.setText("Old email is required.");
            return;
        }
        if (!isEmailValid(oldEmail)) {
            messageLabel.setText("Invalid old email format.");
            return;
        }
        if (newEmail.isEmpty()) {
            messageLabel.setText("New email is required.");
            return;
        }
        if (!isEmailValid(newEmail)) {
            messageLabel.setText("Invalid new email format.");
            return;
        }
        if (confirmPassword.isEmpty()) {
            messageLabel.setText("Confirm password is required.");
            return;
        }

        // Simulate checking the old email and confirm password
        boolean isValidUser = checkOldEmailAndPassword(oldEmail, confirmPassword);

        if (!isValidUser) {
            messageLabel.setText("Invalid old email or confirm password.");
            return;
        }

        // Simulate changing the email
        changeEmail(oldEmail, newEmail);
        messageLabel.setText("Email changed successfully!");
    }

    private boolean isEmailValid(String email) {
        String emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$";
        return email.matches(emailRegex);
    }

    private boolean checkOldEmailAndPassword(String oldEmail, String password) {
        // Simulate checking the user's credentials
        // In a real application, this would involve querying a database
        return "user@example.com".equals(oldEmail) && "password123".equals(password);
    }

    private void changeEmail(String oldEmail, String newEmail) {
        // Simulate changing the email in a database
        // In a real application, this would involve updating a record in a database
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailChanger frame = new EmailChanger();
            frame.setVisible(true);
        });
    }
}