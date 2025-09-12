import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField emailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton loginButton, changeEmailButton;
    private String loggedInEmail = "user@example.com";
    private String password = "password";

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(350, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(4, 2));

        JLabel emailLabel = new JLabel("Email:");
        emailField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordField = new JPasswordField();

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String email = emailField.getText();
                char[] passChars = passwordField.getPassword();
                String confirmPassword = new String(passChars);
                if (email.equals(loggedInEmail) && confirmPassword.equals(password)) {
                    JOptionPane.showMessageDialog(null, "Login successful!");
                    showChangeEmailPanel();
                } else {
                    JOptionPane.showMessageDialog(null, "Invalid email or password.");
                }
            }
        });

        add(emailLabel);
        add(emailField);
        add(passwordLabel);
        add(passwordField);
        add(new JLabel());
        add(loginButton);

        setVisible(true);
    }

    private void showChangeEmailPanel() {
        JFrame changeEmailFrame = new JFrame("Change Email");
        changeEmailFrame.setSize(350, 250);
        changeEmailFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        changeEmailFrame.setLocationRelativeTo(null);
        changeEmailFrame.setLayout(new GridLayout(4, 2));

        JLabel existingEmailLabel = new JLabel("Existing Email:");
        JTextField existingEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String existingEmail = existingEmailField.getText();
                char[] passChars = confirmPasswordField.getPassword();
                String confirmPassword = new String(passChars);
                if (existingEmail.equals(loggedInEmail) && confirmPassword.equals(password)) {
                    loggedInEmail = newEmailField.getText();
                    JOptionPane.showMessageDialog(null, "Email changed successfully!");
                    changeEmailFrame.dispose();
                } else {
                    JOptionPane.showMessageDialog(null, "Invalid existing email or password.");
                }
            }
        });

        changeEmailFrame.add(existingEmailLabel);
        changeEmailFrame.add(existingEmailField);
        changeEmailFrame.add(newEmailLabel);
        changeEmailFrame.add(newEmailField);
        changeEmailFrame.add(confirmPasswordLabel);
        changeEmailFrame.add(confirmPasswordField);
        changeEmailFrame.add(new JLabel());
        changeEmailFrame.add(changeEmailButton);

        changeEmailFrame.setVisible(true);
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}