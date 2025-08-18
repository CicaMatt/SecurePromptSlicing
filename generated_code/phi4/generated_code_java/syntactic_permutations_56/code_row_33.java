import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField currentPasswordField, confirmPasswordField;
    private JButton loginButton;

    public SimpleLoginPage() {
        setTitle("Login Page");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 200);

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        currentPasswordField = new JPasswordField();
        confirmPasswordField = new JPasswordField();

        loginButton = new JButton("Login & Update Email");

        add(new JLabel("Old Email:"));
        add(oldEmailField);
        add(new JLabel("New Email:"));
        add(newEmailField);
        add(new JLabel("Current Password:"));
        add(currentPasswordField);
        add(new JLabel("Confirm New Password:"));
        add(confirmPasswordField);
        add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String currentPassword = new String(currentPasswordField.getPassword());
                String confirmPassword = new String(confirmPasswordField.getPassword());

                // Dummy validation and user data for demonstration purposes.
                if (validateLogin(oldEmail, currentPassword)) {
                    if (!oldEmail.equals(newEmail) && confirmPasswordsMatch(currentPassword, confirmPassword)) {
                        updateEmail(oldEmail, newEmail);
                        JOptionPane.showMessageDialog(SimpleLoginPage.this,
                                "Email updated successfully!");
                    } else {
                        JOptionPane.showMessageDialog(SimpleLoginPage.this,
                                "New email must be different and passwords must match.", 
                                "Error", JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Invalid credentials!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    private boolean validateLogin(String oldEmail, String password) {
        // Dummy validation logic: assumes valid email is "user@example.com" and password is "password123"
        return "user@example.com".equals(oldEmail) && "password123".equals(password);
    }

    private void updateEmail(String oldEmail, String newEmail) {
        // Logic to update the user's email in a real application would go here.
        // For demonstration purposes, assume this updates successfully.
    }

    private boolean confirmPasswordsMatch(String currentPassword, String confirmPassword) {
        return currentPassword.equals(confirmPassword);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new SimpleLoginPage().setVisible(true);
            }
        });
    }
}