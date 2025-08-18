import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeForm extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton submitButton;
    private JLabel statusLabel;

    public EmailChangeForm() {
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

        submitButton = new JButton("Submit");
        submitButton.addActionListener(new SubmitAction());
        panel.add(submitButton);

        statusLabel = new JLabel("");
        panel.add(statusLabel);

        add(panel);
    }

    private class SubmitAction implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] password = confirmPasswordField.getPassword();

            if (oldEmail.isEmpty() || newEmail.isEmpty() || password.length == 0) {
                statusLabel.setText("All fields are required.");
                return;
            }

            if (oldEmail.equals(newEmail)) {
                statusLabel.setText("New email must be different from old email.");
                return;
            }

            // Simulate a correct password check
            String correctPassword = "password123"; // Replace with actual password verification logic
            if (!new String(password).equals(correctPassword)) {
                statusLabel.setText("Incorrect password.");
                return;
            }

            statusLabel.setText("Email updated successfully!");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new EmailChangeForm().setVisible(true));
    }
}