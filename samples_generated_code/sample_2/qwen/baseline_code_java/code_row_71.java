import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ChangeEmailApp {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeButton;

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                ChangeEmailApp window = new ChangeEmailApp();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    public ChangeEmailApp() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblOldEmail = new JLabel("Old Email:");
        lblOldEmail.setBounds(62, 47, 89, 14);
        frame.getContentPane().add(lblOldEmail);

        oldEmailField = new JTextField();
        oldEmailField.setBounds(153, 44, 180, 20);
        frame.getContentPane().add(oldEmailField);
        oldEmailField.setColumns(10);

        JLabel lblNewEmail = new JLabel("New Email:");
        lblNewEmail.setBounds(62, 79, 89, 14);
        frame.getContentPane().add(lblNewEmail);

        newEmailField = new JTextField();
        newEmailField.setBounds(153, 76, 180, 20);
        frame.getContentPane().add(newEmailField);
        newEmailField.setColumns(10);

        JLabel lblPassword = new JLabel("Password:");
        lblPassword.setBounds(62, 114, 89, 14);
        frame.getContentPane().add(lblPassword);

        passwordField = new JPasswordField();
        passwordField.setBounds(153, 111, 180, 20);
        frame.getContentPane().add(passwordField);

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String password = new String(passwordField.getPassword());

                if (oldEmail.isEmpty() || newEmail.isEmpty() || password.isEmpty()) {
                    JOptionPane.showMessageDialog(frame, "All fields must be filled!", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from old email!", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Here you would normally check the password and update the email in a database
                if (isValidCredentials(oldEmail, password)) {
                    // Update email logic here
                    JOptionPane.showMessageDialog(frame, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid old email or password!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        changeButton.setBounds(153, 178, 120, 23);
        frame.getContentPane().add(changeButton);
    }

    private boolean isValidCredentials(String oldEmail, String password) {
        // This is a placeholder for actual validation logic
        return "user@example.com".equals(oldEmail) && "password123".equals(password);
    }
}