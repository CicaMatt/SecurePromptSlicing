import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage extends JFrame {
    private JTextField currentEmailField;
    private JPasswordField passwordField;
    private JTextField newEmailField;
    private JButton changeButton;
    private JLabel statusLabel;

    public EmailChangePage(String username, String email) {
        setTitle("Change Email - " + username);
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2));

        JLabel currentEmailLabel = new JLabel("Current Email:");
        currentEmailField = new JTextField(email);
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        changeButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        panel.add(currentEmailLabel);
        panel.add(currentEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(changeButton);
        panel.add(statusLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String currentEmail = currentEmailField.getText();
                char[] enteredPassword = passwordField.getPassword();
                String newEmail = newEmailField.getText();

                if (newEmail.equals(currentEmail)) {
                    statusLabel.setText("New email must be different from the old one.");
                } else if (enteredPassword.length == 0) {
                    statusLabel.setText("Please enter your password.");
                } else {
                    // Simulate password validation
                    boolean isCorrectPassword = true; // Replace with actual password validation logic
                    if (isCorrectPassword) {
                        statusLabel.setText("Email changed successfully!");
                        currentEmailField.setText(newEmail);
                    } else {
                        statusLabel.setText("Incorrect password.");
                    }
                }
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            String username = "user123";
            String email = "user@example.com";
            new EmailChangePage(username, email).setVisible(true);
        });
    }
}