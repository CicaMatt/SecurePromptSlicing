import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailUpdatePage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton updateButton;
    private JLabel messageLabel;

    public EmailUpdatePage() {
        setTitle("Update Email");
        setSize(400, 250);
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

        updateButton = new JButton("Update");
        updateButton.addActionListener(new UpdateActionListener());
        panel.add(updateButton);

        messageLabel = new JLabel("", SwingConstants.CENTER);
        panel.add(messageLabel);

        add(panel);
    }

    private class UpdateActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] confirmPassword = confirmPasswordField.getPassword();

            if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.length == 0) {
                messageLabel.setText("All fields are required.");
                return;
            }

            String password = new String(confirmPassword);
            if (!password.equals("correctPassword")) { // Replace with actual password check
                messageLabel.setText("Incorrect password.");
                return;
            }

            if (oldEmail.equals(newEmail)) {
                messageLabel.setText("New email must be different from old email.");
                return;
            }

            messageLabel.setText("Email updated successfully!");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailUpdatePage frame = new EmailUpdatePage();
            frame.setVisible(true);
        });
    }
}