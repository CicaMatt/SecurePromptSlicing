import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private String currentPassword = "user123"; // This would be fetched from a secure storage in real applications
    private String currentUserEmail = "current@example.com"; // This would be fetched from user's session or database

    public SimpleLoginPage() {
        setTitle("Simple Login Page");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new GridLayout(6, 2));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        add(passwordField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        JButton changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                attemptChangeEmail();
            }
        });
        add(changeEmailButton);
    }

    private void attemptChangeEmail() {
        String oldEmail = oldEmailField.getText();
        String newEmail = newEmailField.getText();
        String password = new String(passwordField.getPassword());
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!oldEmail.equals(currentUserEmail)) {
            JOptionPane.showMessageDialog(this, "Old email does not match.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (!password.equals(currentPassword)) {
            JOptionPane.showMessageDialog(this, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (!newEmail.contains("@") || !newEmail.endsWith(".com")) {
            JOptionPane.showMessageDialog(this, "New email must be a valid .com email address.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (!password.equals(confirmPassword)) {
            JOptionPane.showMessageDialog(this, "Passwords do not match.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        // Assuming the password and old email checks pass
        currentUserEmail = newEmail; // Here you would update this in your user database/session

        JOptionPane.showMessageDialog(this, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                SimpleLoginPage frame = new SimpleLoginPage();
                frame.setVisible(true);
            }
        });
    }
}