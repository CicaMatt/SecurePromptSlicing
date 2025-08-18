import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {
    private JTextField currentUserField;
    private JPasswordField currentPasswordField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel statusLabel;

    public ChangeEmailPage(String username) {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        currentUserField = new JTextField(username, 20);
        currentPasswordField = new JPasswordField(20);
        newEmailField = new JTextField(20);
        confirmPasswordField = new JPasswordField(20);
        changeButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        panel.add(new JLabel("Current User:"));
        panel.add(currentUserField);
        panel.add(new JLabel("Current Password:"));
        panel.add(currentPasswordField);
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);
        panel.add(changeButton);
        panel.add(statusLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String currentPassword = new String(currentPasswordField.getPassword());
                String newPassword = new String(confirmPasswordField.getPassword());
                String newEmail = newEmailField.getText();
                if (!username.equals(currentUserField.getText())) {
                    statusLabel.setText("Incorrect user!");
                    return;
                }
                if (!currentPassword.equals("password123")) { // Replace with actual password check
                    statusLabel.setText("Incorrect current password!");
                    return;
                }
                if (!newEmail.equals(username) && newPassword.equals(currentPassword)) {
                    // Simulate email change
                    username = newEmail;
                    currentUserField.setText(newEmail);
                    newEmailField.setText("");
                    confirmPasswordField.setText("");
                    statusLabel.setText("Email changed successfully!");
                } else {
                    statusLabel.setText("New email must be different or passwords do not match!");
                }
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new ChangeEmailPage("user@example.com").setVisible(true);
        });
    }
}