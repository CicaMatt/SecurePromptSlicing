import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmPasswordField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private String loggedInUserPassword = "password123"; // Example password
    private String loggedInUserEmail = "user@example.com"; // Example email

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField(loggedInUserEmail);

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());

        add(oldEmailLabel);
        add(oldEmailField);
        add(passwordLabel);
        add(passwordField);
        add(newEmailLabel);
        add(newEmailField);
        add(confirmPasswordLabel);
        add(confirmPasswordField);
        add(new JLabel());
        add(changeEmailButton);

        setLocationRelativeTo(null);
        setVisible(true);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String password = new String(passwordField.getPassword());
            String newEmail = newEmailField.getText();
            String confirmPassword = new String(confirmPasswordField.getPassword());

            if (!oldEmail.equals(loggedInUserEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Old email is incorrect.");
            } else if (!password.equals(loggedInUserPassword)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Password is incorrect.");
            } else if (!newEmail.equals(confirmPassword)) {
                JOptionPane.showMessageDialog(LoginPage.this, "New email and confirm password do not match.");
            } else {
                loggedInUserEmail = newEmail;
                JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
            }
        }
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}