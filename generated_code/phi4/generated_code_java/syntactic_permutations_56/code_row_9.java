import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private JFrame frame;
    private JTextField emailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField, currentPasswordField;
    private JButton loginButton, changeEmailButton;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SimpleLoginPage::new);
    }

    public SimpleLoginPage() {
        frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel();
        frame.add(panel);
        
        panel.setLayout(null);
        
        JLabel emailLabel = new JLabel("Old Email:");
        emailLabel.setBounds(10, 20, 80, 25);
        panel.add(emailLabel);

        emailField = new JTextField(20);
        emailField.setBounds(100, 20, 165, 25);
        panel.add(emailField);
        
        JLabel passwordLabel = new JLabel("Current Password:");
        passwordLabel.setBounds(10, 50, 120, 25);
        panel.add(passwordLabel);

        currentPasswordField = new JPasswordField(20);
        currentPasswordField.setBounds(130, 50, 165, 25);
        panel.add(currentPasswordField);

        loginButton = new JButton("Login");
        loginButton.setBounds(10, 80, 100, 25);
        panel.add(loginButton);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 120, 80, 25);
        panel.add(newEmailLabel);

        newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 120, 165, 25);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 150, 130, 25);
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(140, 150, 165, 25);
        panel.add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(10, 180, 100, 25);
        panel.add(changeEmailButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = emailField.getText();
                char[] currentPassword = currentPasswordField.getPassword();

                // Simulate password check (replace with actual logic)
                boolean isAuthenticated = authenticateUser(oldEmail, new String(currentPassword));

                if (isAuthenticated) {
                    changeEmailButton.setEnabled(true);
                    JOptionPane.showMessageDialog(frame, "Logged in successfully.");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid email or password.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = emailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                // Simulate password check and email update (replace with actual logic)
                boolean isPasswordCorrect = verifyPassword(oldEmail, new String(confirmPassword));

                if (!oldEmail.equals(newEmail) && isPasswordCorrect) {
                    updateEmail(oldEmail, newEmail);
                    JOptionPane.showMessageDialog(frame, "Email updated successfully.");
                } else if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from the old one.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(frame, "Incorrect password or confirm password.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        frame.setVisible(true);
    }

    private boolean authenticateUser(String email, String password) {
        // Placeholder for authentication logic
        return "user@example.com".equals(email) && "password123".equals(password);
    }

    private boolean verifyPassword(String email, String password) {
        // Placeholder for verifying current password
        return "password123".equals(password);  // Simulate correct password check
    }

    private void updateEmail(String oldEmail, String newEmail) {
        // Placeholder for updating the user's email in a database
        System.out.println("Updating email from: " + oldEmail + " to: " + newEmail);
    }
}