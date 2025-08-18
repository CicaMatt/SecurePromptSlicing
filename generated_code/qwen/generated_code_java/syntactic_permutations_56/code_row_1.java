import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private String loggedInUserEmail = "user@example.com"; // Simulated logged-in user email
    private String loggedInUserPassword = "password123"; // Simulated logged-in user password

    public LoginPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        add(oldEmailLabel);
        oldEmailField = new JTextField();
        add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        add(newEmailLabel);
        newEmailField = new JTextField();
        add(newEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        add(passwordLabel);
        passwordField = new JPasswordField();
        add(passwordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());
        add(changeEmailButton);

        setVisible(true);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] passwordChars = passwordField.getPassword();
            String password = new String(passwordChars);

            if (!oldEmail.equals(loggedInUserEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Old email is incorrect.", "Error", JOptionPane.ERROR_MESSAGE);
            } else if (password.equals(loggedInUserPassword)) {
                if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from the old email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    loggedInUserEmail = newEmail;
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            } else {
                JOptionPane.showMessageDialog(LoginPage.this, "Password is incorrect.", "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}