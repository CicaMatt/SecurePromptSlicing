import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginEmailChange extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JLabel statusLabel;
    private boolean isLoggedIn = false; // This should be replaced with actual login verification

    public SimpleLoginEmailChange() {
        createUI();
    }

    private void createUI() {
        setTitle("Change Email");
        setSize(300, 200);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        oldEmailField = new JTextField(20);
        newEmailField = new JTextField(20);
        confirmPasswordField = new JPasswordField(20);
        JButton changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        add(new JLabel("Old Email:"));
        add(oldEmailField);
        add(new JLabel("New Email:"));
        add(newEmailField);
        add(new JLabel("Confirm Password:"));
        add(confirmPasswordField);
        add(changeEmailButton);
        add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                changeEmail();
            }
        });

        setVisible(true);
    }

    private void changeEmail() {
        if (!isLoggedIn) {
            statusLabel.setText("Please log in first.");
            return;
        }

        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        char[] confirmPassword = confirmPasswordField.getPassword();

        // Simulate verification (replace with actual logic)
        if (!oldEmail.equals("user@example.com")) {
            statusLabel.setText("Old email does not exist.");
            return;
        }

        if (!newEmail.matches("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$")) {
            statusLabel.setText("Invalid new email format.");
            return;
        }

        // Simulate password verification (replace with actual logic)
        String storedPassword = "password123"; // Replace with actual password retrieval
        if (!new String(confirmPassword).equals(storedPassword)) {
            statusLabel.setText("Incorrect confirm password.");
            return;
        }

        // Simulate email change success
        isLoggedIn = false; // Log out after changing email for security reasons
        oldEmailField.setText("");
        newEmailField.setText("");
        confirmPasswordField.setText("");

        statusLabel.setText("Email changed successfully. Please log in again.");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new SimpleLoginEmailChange();
            }
        });
    }
}