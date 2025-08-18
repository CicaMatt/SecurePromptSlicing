import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailApp {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField passwordField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

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
        lblOldEmail.setBounds(67, 28, 95, 14);
        frame.getContentPane().add(lblOldEmail);

        oldEmailField = new JTextField();
        oldEmailField.setBounds(172, 25, 180, 20);
        frame.getContentPane().add(oldEmailField);
        oldEmailField.setColumns(10);

        JLabel lblNewEmail = new JLabel("New Email:");
        lblNewEmail.setBounds(67, 59, 95, 14);
        frame.getContentPane().add(lblNewEmail);

        newEmailField = new JTextField();
        newEmailField.setBounds(172, 56, 180, 20);
        frame.getContentPane().add(newEmailField);
        newEmailField.setColumns(10);

        JLabel lblPassword = new JLabel("Password:");
        lblPassword.setBounds(67, 93, 95, 14);
        frame.getContentPane().add(lblPassword);

        passwordField = new JPasswordField();
        passwordField.setBounds(172, 90, 180, 20);
        frame.getContentPane().add(passwordField);

        JLabel lblConfirmPassword = new JLabel("Confirm Password:");
        lblConfirmPassword.setBounds(67, 127, 135, 14);
        frame.getContentPane().add(lblConfirmPassword);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(172, 124, 180, 20);
        frame.getContentPane().add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] password = passwordField.getPassword();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (!new String(password).equals("correctPassword")) {
                    JOptionPane.showMessageDialog(frame, "Incorrect Password", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                if (!new String(password).equals(new String(confirmPassword))) {
                    JOptionPane.showMessageDialog(frame, "Passwords do not match", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from old email", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Simulate changing email
                JOptionPane.showMessageDialog(frame, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
            }
        });
        changeEmailButton.setBounds(172, 160, 180, 30);
        frame.getContentPane().add(changeEmailButton);

        statusLabel = new JLabel("");
        statusLabel.setBounds(172, 205, 180, 14);
        frame.getContentPane().add(statusLabel);
    }
}