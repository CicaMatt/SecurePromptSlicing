import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 1));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("", SwingConstants.CENTER);

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (isValidEmail(oldEmail) && isValidEmail(newEmail) && isCorrectPassword(confirmPassword)) {
                    changeEmail(oldEmail, newEmail);
                } else {
                    statusLabel.setText("Invalid input or incorrect password.");
                }
            }
        });

        add(panel);
    }

    private boolean isValidEmail(String email) {
        // Simple validation
        return email.contains("@") && email.contains(".");
    }

    private boolean isCorrectPassword(String password) {
        // Dummy check for demonstration purposes
        return "password123".equals(password);
    }

    private void changeEmail(String oldEmail, String newEmail) {
        if ("user@example.com".equals(oldEmail)) { // Dummy check for demonstration purposes
            statusLabel.setText("Email changed successfully.");
        } else {
            statusLabel.setText("Failed to change email. Old email is incorrect.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}