import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField emailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton loginButton, changeEmailButton;
    private String loggedInUserEmail = "user@example.com";
    private String loggedInUserPassword = "password";

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(350, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(null);

        JLabel emailLabel = new JLabel("Email:");
        emailLabel.setBounds(10, 10, 80, 25);
        add(emailLabel);

        emailField = new JTextField();
        emailField.setBounds(100, 10, 230, 25);
        add(emailField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 40, 80, 25);
        add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setBounds(100, 40, 230, 25);
        add(passwordField);

        loginButton = new JButton("Login");
        loginButton.setBounds(10, 70, 80, 25);
        loginButton.addActionListener(new LoginActionListener());
        add(loginButton);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 140, 80, 25);
        newEmailLabel.setVisible(false);
        add(newEmailLabel);

        newEmailField = new JTextField();
        newEmailField.setBounds(100, 140, 230, 25);
        newEmailField.setVisible(false);
        add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 170, 120, 25);
        confirmPasswordLabel.setVisible(false);
        add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(130, 170, 200, 25);
        confirmPasswordField.setVisible(false);
        add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(240, 70, 90, 25);
        changeEmailButton.addActionListener(new ChangeEmailActionListener());
        changeEmailButton.setVisible(false);
        add(changeEmailButton);
    }

    private class LoginActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String email = emailField.getText();
            String password = new String(passwordField.getPassword());

            if (email.equals(loggedInUserEmail) && password.equals(loggedInUserPassword)) {
                JOptionPane.showMessageDialog(null, "Login successful!");
                loginButton.setVisible(false);
                emailField.setEditable(false);
                passwordField.setEditable(false);

                newEmailField.setVisible(true);
                confirmPasswordField.setVisible(true);
                changeEmailButton.setVisible(true);
            } else {
                JOptionPane.showMessageDialog(null, "Invalid email or password.");
            }
        }
    }

    private class ChangeEmailActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String currentPassword = new String(passwordField.getPassword());
            String newEmail = newEmailField.getText();
            String confirmPassword = new String(confirmPasswordField.getPassword());

            if (!currentPassword.equals(loggedInUserPassword)) {
                JOptionPane.showMessageDialog(null, "Incorrect password.");
            } else if (newEmail.isEmpty() || newEmail.equals(loggedInUserEmail)) {
                JOptionPane.showMessageDialog(null, "Please enter a valid new email that is different from the current one.");
            } else if (!confirmPassword.equals(currentPassword)) {
                JOptionPane.showMessageDialog(null, "Passwords do not match.");
            } else {
                loggedInUserEmail = newEmail;
                JOptionPane.showMessageDialog(null, "Email changed successfully!");
            }
        }
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