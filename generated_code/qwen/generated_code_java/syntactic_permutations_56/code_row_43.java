import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeEmailButton;
    private String loggedInUserPassword = "password"; // Example password
    private String loggedInUserOldEmail = "user@example.com"; // Example email

    public LoginPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        panel.add(oldEmailLabel);
        panel.add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        panel.add(newEmailLabel);
        panel.add(newEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        panel.add(passwordLabel);
        panel.add(passwordField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());
        panel.add(changeEmailButton);

        add(panel);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            String password = new String(passwordField.getPassword());
            String confirmPassword = new String(confirmPasswordField.getPassword());

            if (!oldEmail.equals(loggedInUserOldEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Incorrect old email.", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            if (!password.equals(loggedInUserPassword)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            if (newEmail.isEmpty() || newEmail.equals(oldEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "New email must be different and not empty.", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            if (!password.equals(confirmPassword)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Passwords do not match.", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            loggedInUserOldEmail = newEmail; // Update email
            JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage loginPage = new LoginPage();
            loginPage.setVisible(true);
        });
    }
}