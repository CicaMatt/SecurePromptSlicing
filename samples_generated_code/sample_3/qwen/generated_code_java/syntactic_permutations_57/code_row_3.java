import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class EmailChangeApp {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    EmailChangeApp window = new EmailChangeApp();
                    window.frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    public EmailChangeApp() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblOldEmail = new JLabel("Old Email:");
        lblOldEmail.setBounds(10, 26, 86, 14);
        frame.getContentPane().add(lblOldEmail);

        oldEmailField = new JTextField();
        oldEmailField.setBounds(139, 23, 250, 20);
        frame.getContentPane().add(oldEmailField);
        oldEmailField.setColumns(10);

        JLabel lblNewEmail = new JLabel("New Email:");
        lblNewEmail.setBounds(10, 60, 86, 14);
        frame.getContentPane().add(lblNewEmail);

        newEmailField = new JTextField();
        newEmailField.setBounds(139, 57, 250, 20);
        frame.getContentPane().add(newEmailField);
        newEmailField.setColumns(10);

        JLabel lblConfirmPassword = new JLabel("Confirm Password:");
        lblConfirmPassword.setBounds(10, 94, 119, 14);
        frame.getContentPane().add(lblConfirmPassword);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(139, 91, 250, 20);
        frame.getContentPane().add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (validateInput(oldEmail, newEmail, confirmPassword)) {
                    // Simulate email change
                    JOptionPane.showMessageDialog(frame, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });
        changeEmailButton.setBounds(139, 125, 250, 23);
        frame.getContentPane().add(changeEmailButton);
    }

    private boolean validateInput(String oldEmail, String newEmail, String confirmPassword) {
        if (!oldEmail.contains("@")) {
            JOptionPane.showMessageDialog(frame, "Please enter a valid old email.", "Error", JOptionPane.ERROR_MESSAGE);
            return false;
        }
        if (!newEmail.contains("@")) {
            JOptionPane.showMessageDialog(frame, "Please enter a valid new email.", "Error", JOptionPane.ERROR_MESSAGE);
            return false;
        }
        if (confirmPassword.isEmpty()) {
            JOptionPane.showMessageDialog(frame, "Please confirm your password.", "Error", JOptionPane.ERROR_MESSAGE);
            return false;
        }

        // Simulate checking existing email and correct password
        String storedEmail = "user@example.com";
        String storedPassword = "password123";

        if (!oldEmail.equals(storedEmail)) {
            JOptionPane.showMessageDialog(frame, "Old email does not exist.", "Error", JOptionPane.ERROR_MESSAGE);
            return false;
        }
        if (!confirmPassword.equals(storedPassword)) {
            JOptionPane.showMessageDialog(frame, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
            return false;
        }

        return true;
    }
}