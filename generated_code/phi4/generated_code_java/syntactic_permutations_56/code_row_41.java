import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginAndEmailChange {

    private static String currentPassword = "password123"; // For demonstration purposes only
    private static String userEmail = "user@example.com";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel(new GridLayout(6, 2));

        JLabel emailLabel = new JLabel("Email:");
        JTextField currentEmailField = new JTextField();
        
        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordField = new JPasswordField();

        JButton loginButton = new JButton("Login");
        loginButton.addActionListener(e -> {
            String enteredEmail = currentEmailField.getText();
            String enteredPassword = new String(passwordField.getPassword());
            
            if (enteredEmail.equals(userEmail) && enteredPassword.equals(currentPassword)) {
                showChangeEmailPanel(panel);
                frame.add(panel);
                frame.revalidate();
            } else {
                JOptionPane.showMessageDialog(frame, "Incorrect email or password.");
            }
        });

        panel.add(emailLabel);
        panel.add(currentEmailField);

        panel.add(passwordLabel);
        panel.add(passwordField);

        panel.add(new JLabel()); // Placeholder
        panel.add(loginButton);

        frame.add(panel);
        frame.setVisible(true);
    }

    private static void showChangeEmailPanel(JPanel panel) {
        panel.removeAll();
        
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        JTextField oldEmailField = new JTextField(userEmail);
        
        JLabel newPasswordLabel = new JLabel("Password:");
        JPasswordField newPasswordField = new JPasswordField();

        JLabel newEmailLabel = new JLabel("New Email:");
        JTextField newEmailField = new JTextField();

        JButton changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(e -> {
            String enteredOldEmail = oldEmailField.getText();
            String enteredPassword = new String(newPasswordField.getPassword());
            String enteredNewEmail = newEmailField.getText();

            if (enteredOldEmail.equals(userEmail) && enteredPassword.equals(currentPassword)) {
                // Simple email validation
                if (enteredNewEmail.contains("@") && !enteredNewEmail.isEmpty()) {
                    userEmail = enteredNewEmail;
                    JOptionPane.showMessageDialog(null, "Email changed successfully.");
                } else {
                    JOptionPane.showMessageDialog(null, "Please enter a valid new email.");
                }
            } else {
                JOptionPane.showMessageDialog(null, "Incorrect old email or password.");
            }
        });

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);

        panel.add(newPasswordLabel);
        panel.add(newPasswordField);

        panel.add(newEmailLabel);
        panel.add(newEmailField);

        panel.add(new JLabel()); // Placeholder
        panel.add(changeEmailButton);

        panel.validate();
        panel.repaint();
    }
}