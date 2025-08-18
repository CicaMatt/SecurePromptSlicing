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

    public EmailChangePage(String currentUser, String currentPassword) {
        setTitle("Change Email");
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        confirmPasswordField = new JPasswordField();
        changeButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);
        panel.add(changeButton);
        panel.add(statusLabel);

        add(panel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.equals(currentUser)) {
                    if (!newEmail.equals(oldEmail)) {
                        if (String.valueOf(confirmPassword).equals(currentPassword)) {
                            statusLabel.setText("Email changed successfully!");
                            // Here you would typically update the user's email in a database
                        } else {
                            statusLabel.setText("Incorrect password.");
                        }
                    } else {
                        statusLabel.setText("New email must be different from old email.");
                    }
                } else {
                    statusLabel.setText("Old email does not match your account.");
                }
            }
        });
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