import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmPasswordField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private String loggedInUserEmail = "user@example.com";
    private String loggedInUserPassword = "password";

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField(15);
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField(15);
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField(15);
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JTextField(15);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailActionListener());

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        add(panel);
    }

    private class ChangeEmailActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            char[] passwordChars = passwordField.getPassword();
            String password = new String(passwordChars);
            String newEmail = newEmailField.getText();
            String confirmPassword = confirmPasswordField.getText();

            if (!oldEmail.equals(loggedInUserEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Old email is incorrect.");
            } else if (!password.equals(loggedInUserPassword)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Password is incorrect.");
            } else if (newEmail.equals(oldEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from old email.");
            } else if (!confirmPassword.equals(password)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Passwords do not match.");
            } else {
                loggedInUserEmail = newEmail;
                JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
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