import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginWithEmailChange {

    private static String currentEmail = "user@example.com";
    private static String password = "password123";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel();

        JLabel emailLabel = new JLabel("Old Email:");
        JTextField oldEmailField = new JTextField(20);

        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordField = new JPasswordField(20);

        JLabel newEmailLabel = new JLabel("New Email:");
        JTextField newEmailField = new JTextField(20);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        JPasswordField confirmPasswordField = new JPasswordField(20);

        JButton changeButton = new JButton("Change Email");

        panel.add(emailLabel);
        panel.add(oldEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeButton);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText().trim();
                String enteredPassword = new String(passwordField.getPassword());
                String newEmail = newEmailField.getText().trim();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!oldEmail.equals(currentEmail)) {
                    JOptionPane.showMessageDialog(frame, "Old email does not match.");
                    return;
                }

                if (!enteredPassword.equals(password)) {
                    JOptionPane.showMessageDialog(frame, "Incorrect password.");
                    return;
                }

                if (!newEmail.equals(enterPassword) || !confirmPassword.equals(newEmail)) {
                    JOptionPane.showMessageDialog(frame, "New emails do not match or are empty.");
                    return;
                }

                if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from old email.");
                    return;
                }

                currentEmail = newEmail;
                JOptionPane.showMessageDialog(frame, "Email changed successfully!");
            }
        });

        frame.add(panel);
        frame.setVisible(true);
    }
}