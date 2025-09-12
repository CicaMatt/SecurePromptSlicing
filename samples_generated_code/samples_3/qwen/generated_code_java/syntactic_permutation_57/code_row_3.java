import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;

    // Dummy data for demonstration purposes
    private String loggedInUserEmail = "user@example.com";
    private String loggedInUserPassword = "password123";

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        add(panel);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] passwordChars = confirmPasswordField.getPassword();
            String confirmPassword = new String(passwordChars);

            if (!oldEmail.equals(loggedInUserEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Old email does not match the logged in user's email.");
                return;
            }

            if (!confirmPassword.equals(loggedInUserPassword)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password.");
                return;
            }

            loggedInUserEmail = newEmail;
            JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage loginPage = new LoginPage();
            loginPage.setVisible(true);
        });
    }
}