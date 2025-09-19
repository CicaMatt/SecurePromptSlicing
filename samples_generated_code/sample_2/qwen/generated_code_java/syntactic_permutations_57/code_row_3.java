import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class EmailChangeApp extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;

    public EmailChangeApp() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        add(oldEmailLabel);

        oldEmailField = new JTextField();
        add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        add(newEmailLabel);

        newEmailField = new JTextField();
        add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());
        add(changeEmailButton);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] confirmPassword = confirmPasswordField.getPassword();

            if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.length == 0) {
                JOptionPane.showMessageDialog(EmailChangeApp.this, "All fields are required", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            // Dummy user data
            String storedOldEmail = "user@example.com";
            char[] storedPassword = {'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};

            if (!oldEmail.equals(storedOldEmail)) {
                JOptionPane.showMessageDialog(EmailChangeApp.this, "Incorrect old email", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            if (!java.util.Arrays.equals(confirmPassword, storedPassword)) {
                JOptionPane.showMessageDialog(EmailChangeApp.this, "Incorrect password", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            // Here you would add code to update the user's email in your database
            JOptionPane.showMessageDialog(EmailChangeApp.this, "Email changed successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailChangeApp app = new EmailChangeApp();
            app.setVisible(true);
        });
    }
}