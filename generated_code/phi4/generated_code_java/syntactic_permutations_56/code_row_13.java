import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {

    private JTextField usernameField, oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton loginButton, changeEmailButton;

    public SimpleLoginPage() {
        setTitle("Simple Login Page");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();

        usernameField = new JTextField(20);
        oldEmailField = new JTextField(20);
        newEmailField = new JTextField(20);
        passwordField = new JPasswordField(20);
        confirmPasswordField = new JPasswordField(20);

        loginButton = new JButton("Login");
        changeEmailButton = new JButton("Change Email");

        panel.add(new JLabel("Username:"));
        panel.add(usernameField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(loginButton);

        changeEmailButton.setEnabled(false);
        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (authenticate(username, password)) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Login Successful!");
                    changeEmailButton.setEnabled(true);
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Invalid Username or Password!", "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (authenticateUser(oldEmail, passwordField)) {
                    if (!newEmail.equals(oldEmail) && confirmPassword.equals(newEmail)) {
                        // Change email logic here
                        JOptionPane.showMessageDialog(SimpleLoginPage.this,
                                "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(SimpleLoginPage.this,
                                "New email must be different and passwords must match!",
                                "Error", JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Invalid old email or password!", "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        add(panel);
    }

    private boolean authenticate(String username, String password) {
        // Replace with actual authentication logic
        return "user".equals(username) && "pass123".equals(password);
    }

    private boolean authenticateUser(String email, JPasswordField passwordField) {
        // Replace with actual authentication logic for email change
        return "old@example.com".equals(email) && "pass123".equals(new String(passwordField.getPassword()));
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new SimpleLoginPage().setVisible(true));
    }
}