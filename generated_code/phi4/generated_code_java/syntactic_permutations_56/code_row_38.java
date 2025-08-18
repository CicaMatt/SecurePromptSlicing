import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginAndEmailChange {

    private static String currentUserEmail = "user@example.com";
    private static String currentPassword = "password123";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login and Email Change");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel emailLabel = new JLabel("Old Email:");
        emailLabel.setBounds(10, 20, 80, 25);
        panel.add(emailLabel);

        JTextField oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 20, 165, 25);
        panel.add(oldEmailField);

        JLabel newPasswordLabel = new JLabel("Password:");
        newPasswordLabel.setBounds(10, 50, 80, 25);
        panel.add(newPasswordLabel);

        JPasswordField passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 50, 165, 25);
        panel.add(passwordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 80, 80, 25);
        panel.add(newEmailLabel);

        JTextField newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 80, 165, 25);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 110, 150, 25);
        panel.add(confirmPasswordLabel);

        JPasswordField confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(100, 110, 165, 25);
        panel.add(confirmPasswordField);

        JButton submitButton = new JButton("Change Email");
        submitButton.setBounds(10, 150, 150, 25);
        panel.add(submitButton);

        JLabel resultLabel = new JLabel("");
        resultLabel.setBounds(10, 190, 300, 25);
        panel.add(resultLabel);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                char[] passwordArray = passwordField.getPassword();
                String password = new String(passwordArray);
                String newEmail = newEmailField.getText();
                char[] confirmPasswordArray = confirmPasswordField.getPassword();
                String confirmPassword = new String(confirmPasswordArray);

                if (oldEmail.equals(currentUserEmail)) {
                    if (password.equals(currentPassword)) {
                        if (!newEmail.isEmpty() && !newEmail.equals(oldEmail) && newEmail.contains("@")) {
                            if (confirmPassword.equals(password)) {
                                currentUserEmail = newEmail;
                                resultLabel.setText("Email changed successfully!");
                            } else {
                                resultLabel.setText("Passwords do not match.");
                            }
                        } else {
                            resultLabel.setText("New email must be different and valid.");
                        }
                    } else {
                        resultLabel.setText("Incorrect password.");
                    }
                } else {
                    resultLabel.setText("Old email does not match.");
                }
            }
        });
    }
}