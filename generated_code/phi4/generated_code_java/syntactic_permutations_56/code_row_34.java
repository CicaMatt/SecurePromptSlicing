import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private String storedPassword = "password123"; // Simulating a stored password
    private String storedEmail = "user@example.com"; // Simulating a stored email

    public SimpleLoginPage() {
        frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel();
        frame.add(panel);
        
        panel.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(10, 20, 80, 25);
        panel.add(oldEmailLabel);

        oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 20, 165, 25);
        panel.add(oldEmailField);

        JLabel emailLabel = new JLabel("New Email:");
        emailLabel.setBounds(10, 50, 80, 25);
        panel.add(emailLabel);

        newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 50, 165, 25);
        panel.add(newEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 80, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 80, 165, 25);
        panel.add(passwordField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 110, 150, 25);
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(100, 110, 165, 25);
        panel.add(confirmPasswordField);

        JButton submitButton = new JButton("Submit");
        submitButton.setBounds(10, 140, 80, 25);
        panel.add(submitButton);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newPassword = new String(passwordField.getPassword());
                String confirmPassword = new String(confirmPasswordField.getPassword());
                String newEmail = newEmailField.getText();

                if (!oldEmail.equals(storedEmail)) {
                    JOptionPane.showMessageDialog(frame, "Old email is incorrect.");
                } else if (!newPassword.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(frame, "Passwords do not match.");
                } else if (newPassword.isEmpty()) {
                    JOptionPane.showMessageDialog(frame, "Please enter a new password.");
                } else if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from the old one.");
                } else if (!storedPassword.equals(new String(passwordField.getPassword()))) {
                    JOptionPane.showMessageDialog(frame, "Current password is incorrect.");
                } else {
                    storedEmail = newEmail;
                    storedPassword = newPassword;
                    JOptionPane.showMessageDialog(frame, "Email updated successfully!");
                }
            }
        });

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SimpleLoginPage::new);
    }
}