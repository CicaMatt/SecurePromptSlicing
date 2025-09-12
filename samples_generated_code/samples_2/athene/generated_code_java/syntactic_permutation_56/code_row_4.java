import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField passwordField;
    private JPasswordField confirmPasswordField;
    private JButton submitButton;

    public LoginPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        submitButton = new JButton("Submit");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(submitButton);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();

                if (passwordChars.length == 0 || confirmPasswordChars.length == 0) {
                    JOptionPane.showMessageDialog(null, "Password and confirm password are required.");
                    return;
                }

                String password = new String(passwordChars);
                String confirmPassword = new String(confirmPasswordChars);

                if (!password.equals("correctPassword")) { // Replace with actual password validation
                    JOptionPane.showMessageDialog(null, "Incorrect password.");
                    return;
                }

                if (!password.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(null, "Passwords do not match.");
                    return;
                }

                if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(null, "New email must be different from old email.");
                    return;
                }

                // Simulate successful change
                JOptionPane.showMessageDialog(null, "Email changed successfully!");
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new LoginPage().setVisible(true));
    }
}