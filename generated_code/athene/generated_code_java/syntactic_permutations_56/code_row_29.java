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

    public EmailChangePage(String username, String password) {
        setTitle("Change Email - " + username);
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        changeButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeButton);
        panel.add(statusLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();
                String confirmPassword = new String(confirmPasswordChars);

                if (!oldEmail.equals(username + "@example.com")) {
                    statusLabel.setText("Old email does not match.");
                } else if (newEmail.isEmpty()) {
                    statusLabel.setText("New email cannot be empty.");
                } else if (newEmail.equals(oldEmail)) {
                    statusLabel.setText("New email must be different from old email.");
                } else if (!confirmPassword.equals(password)) {
                    statusLabel.setText("Incorrect password.");
                } else {
                    statusLabel.setText("Email changed successfully!");
                    // Here you would typically update the user's email in a database
                }
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new EmailChangePage("user@example.com", "password123").setVisible(true);
            }
        });
    }
}