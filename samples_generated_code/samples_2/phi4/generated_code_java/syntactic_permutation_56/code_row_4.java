import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private String currentPassword = "user123"; // Example existing password
    private String currentUserEmail = "user@example.com"; // Example existing email

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SimpleLoginPage::new);
    }

    public SimpleLoginPage() {
        frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        
        JLabel oldEmailLabel = new JLabel("Old Email:");
        panel.add(oldEmailLabel);

        oldEmailField = new JTextField(20);
        panel.add(oldEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        panel.add(passwordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        panel.add(newEmailLabel);

        newEmailField = new JTextField(20);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        panel.add(confirmPasswordField);

        JButton submitButton = new JButton("Submit");
        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                char[] password = passwordField.getPassword();
                String newPassword = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (!oldEmail.equals(currentUserEmail)) {
                    JOptionPane.showMessageDialog(frame, "Old email does not match.");
                    return;
                }

                if (new String(password).equals(currentPassword)) {
                    if (newPassword.equals(new String(confirmPassword))) {
                        if (!newPassword.isEmpty() && !newPassword.equals(oldEmail)) {
                            currentUserEmail = newPassword; // Update user email
                            currentPassword = new String(confirmPassword); // Update password for simplicity

                            JOptionPane.showMessageDialog(frame, "Email and password updated successfully.");
                        } else {
                            JOptionPane.showMessageDialog(frame, "New email must be different from old email.");
                        }
                    } else {
                        JOptionPane.showMessageDialog(frame, "Passwords do not match.");
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Incorrect password.");
                }
            }
        });
        
        panel.add(submitButton);
        frame.add(panel);
        frame.setVisible(true);
    }
}