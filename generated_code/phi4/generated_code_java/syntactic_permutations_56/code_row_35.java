import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private static String currentUserEmail = "user@example.com";
    private static String currentPassword = "password123";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login and Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JTextField emailField = new JTextField(15);
        JPasswordField passwordField = new JPasswordField(15);
        JButton loginButton = new JButton("Login");

        JLabel emailLabel = new JLabel("Email:");
        JLabel passwordLabel = new JLabel("Password:");

        panel.add(emailLabel);
        panel.add(emailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton);

        frame.add(panel, "North");

        JPanel changePanel = new JPanel();
        JTextField oldEmailField = new JTextField(15);
        JTextField newEmailField = new JTextField(15);
        JPasswordField confirmPasswordField = new JPasswordField(15);
        JButton changeButton = new JButton("Change Email");

        JLabel oldEmailLabel = new JLabel("Old Email:");
        JLabel newEmailLabel = new JLabel("New Email:");
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");

        changePanel.add(oldEmailLabel);
        changePanel.add(oldEmailField);
        changePanel.add(newEmailLabel);
        changePanel.add(newEmailField);
        changePanel.add(confirmPasswordLabel);
        changePanel.add(confirmPasswordField);
        changePanel.add(changeButton);

        frame.add(changePanel, "Center");
        changePanel.setVisible(false);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String email = emailField.getText();
                char[] password = passwordField.getPassword();

                if (email.equals(currentUserEmail) && new String(password).equals(currentPassword)) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                    changePanel.setVisible(true);
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid Email or Password");
                }
            }
        });

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.equals(currentUserEmail)) {
                    if (!newEmail.equals(oldEmail)) {
                        if (new String(confirmPassword).equals(currentPassword)) {
                            currentUserEmail = newEmail;
                            JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                        } else {
                            JOptionPane.showMessageDialog(frame, "Incorrect Confirm Password");
                        }
                    } else {
                        JOptionPane.showMessageDialog(frame, "New email must be different from old email.");
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Old email does not match current email.");
                }
            }
        });

        frame.setVisible(true);
    }
}