import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeEmailButton;
    private String loggedInUserPassword = "password123"; // Example password for demonstration
    private String loggedInUserEmail = "user@example.com"; // Example email for demonstration

    public LoginPage() {
        setTitle("Login Page");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText().trim();
                String newEmail = newEmailField.getText().trim();
                String password = new String(passwordField.getPassword());
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!oldEmail.equals(loggedInUserEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Old email does not match.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from old email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!password.equals(loggedInUserPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!password.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Passwords do not match.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    loggedInUserEmail = newEmail;
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully.", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(new JLabel()); // Empty label for spacing
        panel.add(changeEmailButton);

        add(panel);
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