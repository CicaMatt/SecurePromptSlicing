import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmPasswordField;
    private JButton changeEmailButton;
    private String loggedInUserOldEmail = "user@example.com"; // Simulated logged-in user's email

    public LoginPage() {
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

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(new JLabel()); // Empty label for spacing
        panel.add(changeEmailButton);

        add(panel);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            String confirmPassword = confirmPasswordField.getText();

            if (!oldEmail.equals(loggedInUserOldEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Incorrect old email.", "Error", JOptionPane.ERROR_MESSAGE);
            } else if (newEmail.equals(oldEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from the old email.", "Error", JOptionPane.ERROR_MESSAGE);
            } else if (confirmPassword.isEmpty()) {
                JOptionPane.showMessageDialog(LoginPage.this, "Please confirm your password.", "Error", JOptionPane.ERROR_MESSAGE);
            } else {
                // Here you would typically verify the password and update the email in a database
                JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                loggedInUserOldEmail = newEmail; // Update simulated logged-in user's email
            }
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