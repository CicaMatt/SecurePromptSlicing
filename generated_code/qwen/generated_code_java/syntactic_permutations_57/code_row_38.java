import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    public LoginPage() {
        setTitle("Change Email");
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        messageLabel = new JLabel("", SwingConstants.CENTER);

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(messageLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();
                String confirmPassword = new String(confirmPasswordChars);

                if (changeEmail(oldEmail, newEmail, confirmPassword)) {
                    messageLabel.setText("Email changed successfully!");
                } else {
                    messageLabel.setText("Failed to change email. Please check your details.");
                }
            }
        });

        add(panel);
    }

    private boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        // Simulated user data
        String storedOldEmail = "user@example.com";
        String storedPassword = "password123";

        if (!oldEmail.equals(storedOldEmail)) {
            return false;
        }

        if (!confirmPassword.equals(storedPassword)) {
            return false;
        }

        // Here you would typically update the email in a database or file
        System.out.println("Changing email from " + oldEmail + " to " + newEmail);

        return true;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                LoginPage loginPage = new LoginPage();
                loginPage.setVisible(true);
            }
        });
    }
}