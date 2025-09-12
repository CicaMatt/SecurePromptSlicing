import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class ChangeEmailPage {
    private JFrame frame;
    private JTextField emailField, confirmEmailField;
    private JPasswordField passwordField;
    private JButton changeButton;

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                ChangeEmailPage window = new ChangeEmailPage();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    public ChangeEmailPage() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblLoggedInAs = new JLabel("Logged in as: user@example.com");
        lblLoggedInAs.setBounds(12, 12, 269, 15);
        frame.getContentPane().add(lblLoggedInAs);

        JLabel lblNewEmail = new JLabel("New Email:");
        lblNewEmail.setBounds(12, 40, 87, 15);
        frame.getContentPane().add(lblNewEmail);

        emailField = new JTextField();
        emailField.setBounds(120, 38, 302, 19);
        frame.getContentPane().add(emailField);
        emailField.setColumns(10);

        JLabel lblConfirmEmail = new JLabel("Confirm New Email:");
        lblConfirmEmail.setBounds(12, 70, 146, 15);
        frame.getContentPane().add(lblConfirmEmail);

        confirmEmailField = new JTextField();
        confirmEmailField.setBounds(168, 68, 254, 19);
        frame.getContentPane().add(confirmEmailField);
        confirmEmailField.setColumns(10);

        JLabel lblPassword = new JLabel("Password:");
        lblPassword.setBounds(12, 100, 73, 15);
        frame.getContentPane().add(lblPassword);

        passwordField = new JPasswordField();
        passwordField.setBounds(89, 98, 333, 19);
        frame.getContentPane().add(passwordField);

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String email = emailField.getText();
                String confirmEmail = confirmEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if (!email.equals(confirmEmail)) {
                    JOptionPane.showMessageDialog(frame, "New emails do not match.");
                    return;
                }

                if (email.isEmpty() || password.isEmpty()) {
                    JOptionPane.showMessageDialog(frame, "All fields must be filled.");
                    return;
                }

                // Here you would typically check the current password and update the email
                // For this example, we assume the password is correct and emails are different
                String currentUserEmail = "user@example.com";
                if (email.equals(currentUserEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from the current one.");
                    return;
                }

                // Simulate a successful change
                JOptionPane.showMessageDialog(frame, "Email changed successfully!");
            }
        });
        changeButton.setBounds(12, 130, 409, 25);
        frame.getContentPane().add(changeButton);
    }
}