import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmPasswordField;
    private JPasswordField passwordField;
    private JButton loginButton, changeEmailButton;

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(350, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(6, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        add(oldEmailLabel);
        add(oldEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        add(passwordLabel);
        add(passwordField);

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String password = new String(passwordField.getPassword());
                if (isValidCredentials(oldEmail, password)) {
                    JOptionPane.showMessageDialog(null, "Logged in successfully!");
                    showChangeEmailForm();
                } else {
                    JOptionPane.showMessageDialog(null, "Invalid credentials!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        add(loginButton);

        setVisible(true);
    }

    private boolean isValidCredentials(String email, String password) {
        // Dummy check for demonstration purposes
        return "user@example.com".equals(email) && "password123".equals(password);
    }

    private void showChangeEmailForm() {
        JFrame changeEmailFrame = new JFrame("Change Email");
        changeEmailFrame.setSize(350, 250);
        changeEmailFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        changeEmailFrame.setLayout(new GridLayout(6, 2));

        JLabel currentEmailLabel = new JLabel("Current Email:");
        JTextField currentEmailField = new JTextField();
        changeEmailFrame.add(currentEmailLabel);
        changeEmailFrame.add(currentEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        changeEmailFrame.add(newEmailLabel);
        add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        changeEmailFrame.add(confirmPasswordLabel);
        changeEmailFrame.add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String currentEmail = currentEmailField.getText();
                String newPassword = new String(confirmPasswordField.getPassword());
                String newEmail = newEmailField.getText();
                if (isValidCredentials(currentEmail, newPassword) && !newEmail.isEmpty()) {
                    JOptionPane.showMessageDialog(null, "Email changed successfully!");
                    changeEmailFrame.dispose();
                } else {
                    JOptionPane.showMessageDialog(null, "Invalid credentials or empty email!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        changeEmailFrame.add(changeEmailButton);

        changeEmailFrame.setVisible(true);
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}