import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private static String currentEmail = "user@example.com"; // Simulated logged-in user's email
    private static String password = "password123"; // Simulated logged-in user's password

    public static void main(String[] args) {
        JFrame frame = new JFrame("Simple Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

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

        JButton submitButton = new JButton("Change Email");
        submitButton.setBounds(10, 110, 250, 25);
        panel.add(submitButton);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                String newPassword = new String(passwordChars);
                String newEmail = newEmailField.getText();

                if (oldEmail.equals(currentEmail)) {
                    if (newPassword.equals(password)) {
                        if (!newEmail.equals(oldEmail) && !newEmail.isEmpty()) {
                            currentEmail = newEmail;
                            JOptionPane.showMessageDialog(null, "Email changed successfully!");
                        } else {
                            JOptionPane.showMessageDialog(null, "New email must be different and not empty.");
                        }
                    } else {
                        JOptionPane.showMessageDialog(null, "Incorrect password.");
                    }
                } else {
                    JOptionPane.showMessageDialog(null, "Old email does not match the current email.");
                }
            }
        });
    }
}