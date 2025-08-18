import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JButton changeEmailButton;
    private JPanel loginPanel;
    private JPanel changeEmailPanel;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;

    public LoginPage() {
        setTitle("Login Page");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        loginPanel = new JPanel();
        changeEmailPanel = new JPanel();
        setupLoginPanel();
        add(loginPanel);
    }

    private void setupLoginPanel() {
        loginPanel.setLayout(new GridLayout(3, 2));
        JLabel usernameLabel = new JLabel("Username:");
        usernameField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        loginButton = new JButton("Login");
        loginButton.addActionListener(new LoginActionListener());

        loginPanel.add(usernameLabel);
        loginPanel.add(usernameField);
        loginPanel.add(passwordLabel);
        loginPanel.add(passwordField);
        loginPanel.add(new JLabel());
        loginPanel.add(loginButton);
    }

    private void setupChangeEmailPanel() {
        changeEmailPanel.setLayout(new GridLayout(5, 2));
        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailActionListener());

        changeEmailPanel.add(oldEmailLabel);
        changeEmailPanel.add(oldEmailField);
        changeEmailPanel.add(newEmailLabel);
        changeEmailPanel.add(newEmailField);
        changeEmailPanel.add(confirmPasswordLabel);
        changeEmailPanel.add(confirmPasswordField);
        changeEmailPanel.add(new JLabel());
        changeEmailPanel.add(changeEmailButton);
    }

    private class LoginActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String username = usernameField.getText();
            char[] passwordChars = passwordField.getPassword();
            String password = new String(passwordChars);

            if (username.equals("testUser") && password.equals("password")) {
                loginPanel.setVisible(false);
                setupChangeEmailPanel();
                add(changeEmailPanel);
                revalidate();
                repaint();
            } else {
                JOptionPane.showMessageDialog(LoginPage.this, "Invalid username or password", "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private class ChangeEmailActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] confirmPasswordChars = confirmPasswordField.getPassword();
            String confirmPassword = new String(confirmPasswordChars);

            if (newEmail.equals(oldEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from the old email", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            if (!confirmPassword.equals("password")) {
                JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage frame = new LoginPage();
            frame.setVisible(true);
        });
    }
}