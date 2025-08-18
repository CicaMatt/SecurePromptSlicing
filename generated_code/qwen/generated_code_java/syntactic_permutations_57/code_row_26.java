import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 1));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(changeEmailButton);
        panel.add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String password = new String(passwordField.getPassword());
                String newEmail = newEmailField.getText();

                if (changeEmail(oldEmail, password, newEmail)) {
                    statusLabel.setText("Email changed successfully!");
                } else {
                    statusLabel.setText("Failed to change email. Please check your details.");
                }
            }
        });

        add(panel);
    }

    private boolean changeEmail(String oldEmail, String password, String newEmail) {
        // Dummy data for demonstration purposes
        String correctOldEmail = "user@example.com";
        String correctPassword = "password123";

        if (!oldEmail.equals(correctOldEmail)) {
            return false;
        }
        if (!password.equals(correctPassword)) {
            return false;
        }

        // Simulate email change process here
        // For demonstration, we just assume the new email is set successfully
        System.out.println("Changing email from " + oldEmail + " to " + newEmail);
        return true;
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