import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {
    private static String userEmail = "user@example.com";
    private static String userPassword = "password123";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(10, 10, 80, 25);
        panel.add(oldEmailLabel);

        JTextField oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 10, 160, 25);
        panel.add(oldEmailField);

        JLabel newPasswordLabel = new JLabel("Password:");
        newPasswordLabel.setBounds(10, 40, 80, 25);
        panel.add(newPasswordLabel);

        JPasswordField passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 40, 160, 25);
        panel.add(passwordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 70, 80, 25);
        panel.add(newEmailLabel);

        JTextField newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 70, 160, 25);
        panel.add(newEmailField);

        JButton changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(10, 100, 150, 25);
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                char[] password = passwordField.getPassword();
                String newPassword = new String(password);
                String newEmail = newEmailField.getText();

                if (oldEmail.equals(userEmail) && newPassword.equals(userPassword)) {
                    if (!newEmail.isEmpty() && !newEmail.equals(userEmail)) {
                        userEmail = newEmail;
                        JOptionPane.showMessageDialog(panel, "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(panel, "New email must be different from the old email.", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(panel, "Invalid credentials!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }
}