import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginAndChangeEmail extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton loginButton, changeEmailButton;
    private String currentPassword = "password123"; // Placeholder for demonstration
    private String userEmail = "user@example.com";   // Placeholder for demonstration

    public LoginAndChangeEmail() {
        createUI();
    }

    private void createUI() {
        setTitle("Login and Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();

        oldEmailField = new JTextField(20);
        newEmailField = new JTextField(20);
        passwordField = new JPasswordField(20);
        confirmPasswordField = new JPasswordField(20);

        loginButton = new JButton("Login");
        changeEmailButton = new JButton("Change Email");

        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String enteredEmail = oldEmailField.getText();
                String enteredPassword = new String(passwordField.getPassword());

                if (enteredEmail.equals(userEmail) && enteredPassword.equals(currentPassword)) {
                    JOptionPane.showMessageDialog(LoginAndChangeEmail.this, "Login Successful!");
                } else {
                    JOptionPane.showMessageDialog(LoginAndChangeEmail.this, "Invalid credentials.");
                }
            }
        });

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] password = passwordField.getPassword();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (!oldEmail.equals(userEmail)) {
                    JOptionPane.showMessageDialog(LoginAndChangeEmail.this, "Old email is incorrect.");
                    return;
                }

                if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(LoginAndChangeEmail.this, "New email must be different.");
                    return;
                }

                String enteredPassword = new String(password);
                String confirmEnteredPassword = new String(confirmPassword);

                if (!enteredPassword.equals(currentPassword)) {
                    JOptionPane.showMessageDialog(LoginAndChangeEmail.this, "Invalid password.");
                    return;
                }

                if (!confirmEnteredPassword.equals(enteredPassword)) {
                    JOptionPane.showMessageDialog(LoginAndChangeEmail.this, "Passwords do not match.");
                    return;
                }

                // Simulating email change
                userEmail = newEmail;
                JOptionPane.showMessageDialog(LoginAndChangeEmail.this, "Email changed successfully to: " + userEmail);
            }
        });

        panel.add(loginButton);
        panel.add(changeEmailButton);

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginAndChangeEmail().setVisible(true);
            }
        });
    }
}