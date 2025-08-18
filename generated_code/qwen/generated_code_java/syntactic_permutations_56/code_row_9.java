import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmPasswordField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private String correctPassword = "password123";
    private String currentEmail = "user@example.com";

    public LoginPage() {
        setTitle("Login to Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField(currentEmail);
        panel.add(oldEmailLabel);
        panel.add(oldEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        panel.add(passwordLabel);
        panel.add(passwordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        panel.add(newEmailLabel);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String password = new String(passwordField.getPassword());
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!oldEmail.equals(currentEmail)) {
                    JOptionPane.showMessageDialog(null, "Old email is incorrect.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!password.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(null, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (newEmail.isEmpty()) {
                    JOptionPane.showMessageDialog(null, "New email cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(null, "New email must be different from old email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!confirmPassword.equals(password)) {
                    JOptionPane.showMessageDialog(null, "Passwords do not match.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    currentEmail = newEmail;
                    JOptionPane.showMessageDialog(null, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });

        panel.add(changeEmailButton);

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}