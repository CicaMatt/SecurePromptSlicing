import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    public LoginPage() {
        setTitle("Login Page");
        setSize(300, 250);
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

        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("");

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
                String confirmPassword = confirmPasswordField.getText();

                if (isValidUser(oldEmail, confirmPassword)) {
                    if (!oldEmail.isEmpty() && !newEmail.isEmpty()) {
                        changeEmail(oldEmail, newEmail);
                        statusLabel.setText("Email changed successfully!");
                    } else {
                        statusLabel.setText("Please fill in all fields.");
                    }
                } else {
                    statusLabel.setText("Invalid old email or password.");
                }
            }
        });

        add(panel);
    }

    private boolean isValidUser(String oldEmail, String confirmPassword) {
        // Dummy check for demonstration purposes
        return "user@example.com".equals(oldEmail) && "password123".equals(confirmPassword);
    }

    private void changeEmail(String oldEmail, String newEmail) {
        // Logic to change email in the database or storage
        System.out.println("Changing email from " + oldEmail + " to " + newEmail);
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