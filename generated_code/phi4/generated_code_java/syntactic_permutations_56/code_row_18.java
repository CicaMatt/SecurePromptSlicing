import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLogin {

    private static String currentPassword = "password123"; // Simulated current password for demo purposes
    private static String userEmail = "user@example.com"; // Simulated user email for demo purposes

    public static void main(String[] args) {
        JFrame frame = new JFrame("Simple Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 250);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(10, 20, 80, 25);
        panel.add(oldEmailLabel);

        JTextField oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 20, 165, 25);
        panel.add(oldEmailField);

        JLabel newPasswordLabel = new JLabel("New Email:");
        newPasswordLabel.setBounds(10, 50, 80, 25);
        panel.add(newPasswordLabel);

        JTextField newPasswordField = new JTextField(20);
        newPasswordField.setBounds(100, 50, 165, 25);
        panel.add(newPasswordField);

        JLabel passwordConfirmLabel = new JLabel("Confirm Password:");
        passwordConfirmLabel.setBounds(10, 80, 120, 25);
        panel.add(passwordConfirmLabel);

        JPasswordField confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(130, 80, 135, 25);
        panel.add(confirmPasswordField);

        JButton loginButton = new JButton("Login");
        loginButton.setBounds(10, 110, 250, 25);
        panel.add(loginButton);

        JLabel messageLabel = new JLabel("");
        messageLabel.setBounds(10, 150, 250, 25);
        panel.add(messageLabel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newPassword = newPasswordField.getText();
                char[] password = confirmPasswordField.getPassword();

                if (!oldEmail.equals(userEmail)) {
                    messageLabel.setText("Old email does not match.");
                    return;
                }

                if (newPassword.equals(oldEmail)) {
                    messageLabel.setText("New email must be different from old email.");
                    return;
                }

                String inputPassword = new String(password);
                if (!inputPassword.equals(currentPassword)) {
                    messageLabel.setText("Incorrect current password.");
                    return;
                }

                // Update user details (simulated)
                userEmail = newPassword;
                JOptionPane.showMessageDialog(panel, "Email updated successfully!");
            }
        });
    }
}