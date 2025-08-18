import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel statusLabel;

    public EmailChangePage() {
        setTitle("Email Change");
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

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
        statusLabel = new JLabel("");

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (isValidUser(oldEmail, confirmPassword)) {
                    updateEmail(oldEmail, newEmail);
                    statusLabel.setText("Email changed successfully!");
                } else {
                    statusLabel.setText("Invalid old email or password.");
                }
            }

            private boolean isValidUser(String email, char[] password) {
                // Simulate user validation
                return "user@example.com".equals(email) && "password123".equals(new String(password));
            }

            private void updateEmail(String oldEmail, String newEmail) {
                // Simulate email update
                System.out.println("Updating email from: " + oldEmail + " to: " + newEmail);
            }
        });

        panel.add(changeButton);
        panel.add(statusLabel);

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailChangePage frame = new EmailChangePage();
            frame.setVisible(true);
        });
    }
}