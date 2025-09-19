import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeEmailButton;
    private String loggedInUserOldEmail = "user@example.com";
    private String loggedInUserPassword = "password";

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(6, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        add(oldEmailLabel);
        add(oldEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        add(passwordLabel);
        add(passwordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        add(newEmailLabel);
        add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordLabel);
        add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                char[] password = passwordField.getPassword();
                String newPassword = new String(password);
                String newEmail = newEmailField.getText();
                char[] confirmPasswordArray = confirmPasswordField.getPassword();
                String confirmPassword = new String(confirmPasswordArray);

                if (oldEmail.equals(loggedInUserOldEmail) && newPassword.equals(loggedInUserPassword)
                        && newEmail.length() > 0 && !newEmail.equals(oldEmail)
                        && newPassword.equals(confirmPassword)) {
                    loggedInUserOldEmail = newEmail;
                    JOptionPane.showMessageDialog(null, "Email changed successfully!");
                } else if (!oldEmail.equals(loggedInUserOldEmail)) {
                    JOptionPane.showMessageDialog(null, "Incorrect old email.");
                } else if (!newPassword.equals(loggedInUserPassword)) {
                    JOptionPane.showMessageDialog(null, "Incorrect password.");
                } else if (newEmail.length() == 0) {
                    JOptionPane.showMessageDialog(null, "New email cannot be empty.");
                } else if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(null, "New email must be different from the old email.");
                } else if (!newPassword.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(null, "Passwords do not match.");
                }
            }
        });
        add(changeEmailButton);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}