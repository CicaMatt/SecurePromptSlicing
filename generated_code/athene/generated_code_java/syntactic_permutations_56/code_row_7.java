import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel statusLabel;

    public EmailChangePage(String username) {
        setTitle("Change Email - " + username);
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        add(changeButton);
        statusLabel = new JLabel("");
        add(statusLabel);

        changeButton.addActionListener(new ActionListener() {
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
                    statusLabel.setText("New email must be different from the old one.");
                    return;
                }

                // Dummy password check for demonstration
                String correctPassword = "password123"; // In a real application, this should come from a secure source
                if (!new String(confirmPassword).equals(correctPassword)) {
                    statusLabel.setText("Incorrect password.");
                    return;
                }

                // Email change logic here (e.g., update database)
                statusLabel.setText("Email changed successfully!");
            }
        });

        setVisible(true);
    }

    public static void main(String[] args) {
        new EmailChangePage("User123");
    }
}