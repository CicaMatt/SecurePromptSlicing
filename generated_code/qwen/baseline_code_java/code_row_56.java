import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeButton;
    private String currentPassword = "password123"; // Example stored password
    private String currentEmail = "user@example.com"; // Example stored email

    public ChangeEmailPage() {
        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);
        frame.setLayout(new GridLayout(6, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        changeButton = new JButton("Change Email");

        frame.add(oldEmailLabel);
        frame.add(oldEmailField);
        frame.add(newEmailLabel);
        frame.add(newEmailField);
        frame.add(passwordLabel);
        frame.add(passwordField);
        frame.add(confirmPasswordLabel);
        frame.add(confirmPasswordField);
        frame.add(changeButton);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String password = new String(passwordField.getPassword());
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!oldEmail.equals(currentEmail)) {
                    JOptionPane.showMessageDialog(frame, "Old email does not match.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email cannot be the same as old email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!password.equals(currentPassword)) {
                    JOptionPane.showMessageDialog(frame, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!password.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(frame, "Passwords do not match.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    currentEmail = newEmail;
                    JOptionPane.showMessageDialog(frame, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                    frame.dispose();
                }
            }
        });

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new ChangeEmailPage();
            }
        });
    }
}