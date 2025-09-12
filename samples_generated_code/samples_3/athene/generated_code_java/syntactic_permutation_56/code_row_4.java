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
        setTitle("Change Email");
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

        statusLabel = new JLabel("");
        panel.add(statusLabel);

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ChangeEmailActionListener());
        panel.add(changeButton);

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

            if (oldEmail.equals(newEmail)) {
                statusLabel.setText("New email must be different from the old email.");
                return;
            }

            // Dummy password check, replace with actual authentication
            String correctPassword = "password123";
            if (!new String(confirmPassword).equals(correctPassword)) {
                statusLabel.setText("Incorrect password.");
                return;
            }

            statusLabel.setText("Email changed successfully!");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailChangePage frame = new EmailChangePage();
            frame.setVisible(true);
        });
    }
}