import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginEmailChanger {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField passwordField;
    private JPasswordField confirmPasswordField;
    private String currentPassword = "password123"; // Dummy current password
    private String userEmail = "user@example.com";  // Dummy user email

    public LoginEmailChanger() {
        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        panel.add(oldEmailLabel);
        
        oldEmailField = new JTextField();
        panel.add(oldEmailField);

        JLabel newPasswordLabel = new JLabel("Password:");
        panel.add(newPasswordLabel);
        
        passwordField = new JPasswordField();
        panel.add(passwordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        panel.add(newEmailLabel);
        
        newEmailField = new JTextField();
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        panel.add(confirmPasswordLabel);
        
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordField);

        JButton changeButton = new JButton("Change Email");
        panel.add(changeButton);

        frame.add(panel);
        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                attemptEmailChange();
            }
        });

        frame.setVisible(true);
    }

    private void attemptEmailChange() {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        String password = new String(passwordField.getPassword());
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!oldEmail.equals(userEmail)) {
            JOptionPane.showMessageDialog(frame, "Old email does not match.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (!password.equals(currentPassword)) {
            JOptionPane.showMessageDialog(frame, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (newEmail.isEmpty() || !newEmail.contains("@")) {
            JOptionPane.showMessageDialog(frame, "Invalid new email format.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (!newEmail.equals(oldEmail)) {
            if (confirmPassword.equals(password) && !newEmail.equals(oldEmail)) {
                userEmail = newEmail;
                JOptionPane.showMessageDialog(frame, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
            } else {
                JOptionPane.showMessageDialog(frame, "Confirm password does not match.", "Error", JOptionPane.ERROR_MESSAGE);
            }
        } else {
            JOptionPane.showMessageDialog(frame, "New email must be different from the old email.", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(LoginEmailChanger::new);
    }
}