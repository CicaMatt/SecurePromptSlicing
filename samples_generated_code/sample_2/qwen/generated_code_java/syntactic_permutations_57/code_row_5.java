import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class ChangeEmailApp {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
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
        oldEmailField.setBounds(150, 44, 230, 20);
        frame.getContentPane().add(oldEmailField);
        oldEmailField.setColumns(10);

        JLabel lblNewEmail = new JLabel("New Email:");
        lblNewEmail.setBounds(62, 89, 89, 14);
        frame.getContentPane().add(lblNewEmail);

        newEmailField = new JTextField();
        newEmailField.setBounds(150, 86, 230, 20);
        frame.getContentPane().add(newEmailField);
        newEmailField.setColumns(10);

        JLabel lblConfirmPassword = new JLabel("Confirm Password:");
        lblConfirmPassword.setBounds(62, 127, 149, 14);
        frame.getContentPane().add(lblConfirmPassword);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(150, 124, 230, 20);
        frame.getContentPane().add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (validateInput(oldEmail, newEmail, confirmPassword)) {
                    // Simulate email change process
                    JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid input or incorrect password!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        changeButton.setBounds(160, 178, 132, 23);
        frame.getContentPane().add(changeButton);
    }

    private boolean validateInput(String oldEmail, String newEmail, String confirmPassword) {
        // Simulated user data
        final String USER_OLD_EMAIL = "user@example.com";
        final String USER_PASSWORD = "password";

        return oldEmail.equals(USER_OLD_EMAIL) && !newEmail.isEmpty() && confirmPassword.equals(USER_PASSWORD);
    }
}