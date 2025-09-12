import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ChangeEmailApp {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeButton;

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    ChangeEmailApp window = new ChangeEmailApp();
                    window.frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
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
        lblOldEmail.setBounds(27, 26, 98, 14);
        frame.getContentPane().add(lblOldEmail);

        oldEmailField = new JTextField();
        oldEmailField.setBounds(135, 23, 260, 20);
        frame.getContentPane().add(oldEmailField);
        oldEmailField.setColumns(10);

        JLabel lblNewEmail = new JLabel("New Email:");
        lblNewEmail.setBounds(27, 64, 98, 14);
        frame.getContentPane().add(lblNewEmail);

        newEmailField = new JTextField();
        newEmailField.setBounds(135, 61, 260, 20);
        frame.getContentPane().add(newEmailField);
        newEmailField.setColumns(10);

        JLabel lblPassword = new JLabel("Password:");
        lblPassword.setBounds(27, 102, 98, 14);
        frame.getContentPane().add(lblPassword);

        passwordField = new JPasswordField();
        passwordField.setBounds(135, 99, 260, 20);
        frame.getContentPane().add(passwordField);

        JLabel lblConfirmPassword = new JLabel("Confirm Password:");
        lblConfirmPassword.setBounds(27, 140, 116, 14);
        frame.getContentPane().add(lblConfirmPassword);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(153, 137, 242, 20);
        frame.getContentPane().add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();

                String password = new String(passwordChars);
                String confirmPassword = new String(confirmPasswordChars);

                if (oldEmail.isEmpty() || newEmail.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
                    JOptionPane.showMessageDialog(frame, "All fields are required!", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!password.equals("correctPassword")) {
                    JOptionPane.showMessageDialog(frame, "Incorrect password!", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from the old email!", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!password.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(frame, "Passwords do not match!", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(frame, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });
        changeButton.setBounds(163, 189, 120, 23);
        frame.getContentPane().add(changeButton);
    }
}