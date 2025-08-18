import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel statusLabel;

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        panel.add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        panel.add(oldEmailField);

        panel.add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        panel.add(newEmailField);

        panel.add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ChangeEmailActionListener());
        panel.add(changeButton);

        statusLabel = new JLabel("");
        panel.add(statusLabel);

        add(panel);
    }

    private class ChangeEmailActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] confirmPassword = confirmPasswordField.getPassword();

            if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.length == 0) {
                statusLabel.setText("All fields are required.");
                return;
            }

            // Simulate password verification
            boolean isCorrectPassword = true; // Replace with actual password validation logic

            if (!isCorrectPassword) {
                statusLabel.setText("Incorrect password.");
                return;
            }

            if (newEmail.equals(oldEmail)) {
                statusLabel.setText("New email cannot be the same as old email.");
                return;
            }

            // Simulate email format validation
            boolean isValidEmail = newEmail.matches("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
            if (!isValidEmail) {
                statusLabel.setText("Invalid email format.");
                return;
            }

            // Simulate email update
            statusLabel.setText("Email changed successfully.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new ChangeEmailPage().setVisible(true);
        });
    }
}