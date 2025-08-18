import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel messageLabel;
    private String loggedUserOldEmail = "user@example.com";
    private String loggedUserPassword = "password123";

    public EmailChangePage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeButton = new JButton("Change Email");
        messageLabel = new JLabel("");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeButton);
        panel.add(messageLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();
                String password = new String(confirmPassword);

                if (loggedUserOldEmail.equals(oldEmail) && loggedUserPassword.equals(password)) {
                    if (!oldEmail.equals(newEmail)) {
                        loggedUserOldEmail = newEmail;
                        messageLabel.setText("Email changed successfully.");
                    } else {
                        messageLabel.setText("New email must be different from old email.");
                    }
                } else {
                    messageLabel.setText("Incorrect old email or password.");
                }
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailChangePage page = new EmailChangePage();
            page.setVisible(true);
        });
    }
}