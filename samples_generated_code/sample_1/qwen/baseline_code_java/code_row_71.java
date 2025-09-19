import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeEmailButton;
    private String currentEmail = "user@example.com";
    private String currentPassword = "password123";

    public LoginPage() {
        setTitle("Login Page");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

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
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String password = new String(passwordField.getPassword());
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!oldEmail.equals(currentEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect old email.");
                } else if (!password.equals(currentPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password.");
                } else if (newEmail.isEmpty()) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email cannot be empty.");
                } else if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from old email.");
                } else if (!confirmPassword.equals(password)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Passwords do not match.");
                } else {
                    currentEmail = newEmail;
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully.");
                    clearFields();
                }
            }
        });
        add(changeEmailButton);
    }

    private void clearFields() {
        oldEmailField.setText("");
        passwordField.setText("");
        newEmailField.setText("");
        confirmPasswordField.setText("");
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