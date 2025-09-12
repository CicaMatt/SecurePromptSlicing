import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class ChangeEmailPage {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeButton;

    public ChangeEmailPage() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame("Change Email");
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(new GridLayout(6, 2));

        JLabel lblOldEmail = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel lblNewEmail = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel lblPassword = new JLabel("Password:");
        passwordField = new JPasswordField();
        JLabel lblConfirmPassword = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] password = passwordField.getPassword();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (!String.valueOf(password).equals(String.valueOf(confirmPassword))) {
                    JOptionPane.showMessageDialog(frame, "Passwords do not match!");
                    return;
                }

                // Here we assume the user is already logged in and their credentials are correct
                // This is a placeholder for actual password verification logic
                String loggedInUserEmail = "user@example.com"; // Simulated logged-in user email
                String loggedInUserPassword = "password"; // Simulated logged-in user password

                if (!oldEmail.equals(loggedInUserEmail)) {
                    JOptionPane.showMessageDialog(frame, "Old Email does not match!");
                    return;
                }

                if (String.valueOf(password).equals(loggedInUserPassword)) {
                    if (newEmail.equals(oldEmail)) {
                        JOptionPane.showMessageDialog(frame, "New email must be different from old email.");
                    } else {
                        // Logic to change the user's email
                        JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                        // Clear fields after successful submission
                        oldEmailField.setText("");
                        newEmailField.setText("");
                        passwordField.setText("");
                        confirmPasswordField.setText("");
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Incorrect Password!");
                }
            }
        });

        frame.getContentPane().add(lblOldEmail);
        frame.getContentPane().add(oldEmailField);
        frame.getContentPane().add(lblNewEmail);
        frame.getContentPane().add(newEmailField);
        frame.getContentPane().add(lblPassword);
        frame.getContentPane().add(passwordField);
        frame.getContentPane().add(lblConfirmPassword);
        frame.getContentPane().add(confirmPasswordField);
        frame.getContentPane().add(changeButton);

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    new ChangeEmailPage();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}