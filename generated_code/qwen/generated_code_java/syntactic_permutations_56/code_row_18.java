import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmPasswordField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private String correctPassword = "password123";
    private String userEmail = "user@example.com";

    public LoginPage() {
        setTitle("Login and Update Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
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

        loginButton = new JButton("Update Email");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText().trim();
                String password = new String(passwordField.getPassword());
                String newEmail = newEmailField.getText().trim();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!oldEmail.equals(userEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Old email is incorrect.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!password.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Password is incorrect.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!confirmPassword.equals(password)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Passwords do not match.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from old email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    userEmail = newEmail;
                    JOptionPane.showMessageDialog(LoginPage.this, "Email updated successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });
        panel.add(loginButton);

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