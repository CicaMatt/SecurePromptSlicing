import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField passwordField;
    private JPasswordField confirmPasswordField;
    
    // Hardcoded for demonstration purposes
    private final String currentEmail = "user@example.com";
    private final String correctPassword = "password123";

    public SimpleLoginPage() {
        setTitle("Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel(new GridLayout(5, 2));

        panel.add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        panel.add(oldEmailField);

        panel.add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        panel.add(newEmailField);

        panel.add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        panel.add(passwordField);

        panel.add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordField);

        JButton changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                changeEmail();
            }
        });
        panel.add(changeButton);

        add(panel);
    }

    private void changeEmail() {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        String password = new String(passwordField.getPassword());
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!oldEmail.equals(currentEmail)) {
            JOptionPane.showMessageDialog(this, "Old email is incorrect.");
            return;
        }

        if (!password.equals(correctPassword)) {
            JOptionPane.showMessageDialog(this, "Password is incorrect.");
            return;
        }
        
        if (!newEmail.equals(passwordField.getText())) {
            JOptionPane.showMessageDialog(this, "New emails do not match.");
            return;
        }

        if (oldEmail.equals(newEmail)) {
            JOptionPane.showMessageDialog(this, "Old and new email must be different.");
            return;
        }

        // Simulate changing the email by updating currentEmail
        currentEmail = newEmail;

        JOptionPane.showMessageDialog(this, "Email changed successfully!");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SimpleLoginPage frame = new SimpleLoginPage();
            frame.setVisible(true);
        });
    }
}