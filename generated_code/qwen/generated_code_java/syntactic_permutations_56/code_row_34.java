import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton updateButton;
    private String correctPassword = "password123"; // Example correct password

    public LoginPage() {
        setTitle("Login and Update Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        JLabel newEmailLabel = new JLabel("New Email:");
        JLabel passwordLabel = new JLabel("Password:");
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        passwordField = new JPasswordField();
        confirmPasswordField = new JPasswordField();

        updateButton = new JButton("Update");
        updateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();

                String password = new String(passwordChars);
                String confirmPassword = new String(confirmPasswordChars);

                if (password.equals(correctPassword)) {
                    if (!newEmail.isEmpty() && !oldEmail.isEmpty() && newEmail.equals(confirmPassword)) {
                        JOptionPane.showMessageDialog(LoginPage.this, "New email and confirm password must be different.");
                    } else if (!newEmail.equals(oldEmail)) {
                        JOptionPane.showMessageDialog(LoginPage.this, "Email updated successfully!");
                    } else {
                        JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from old email.");
                    }
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password.");
                }
            }
        });

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(updateButton);

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