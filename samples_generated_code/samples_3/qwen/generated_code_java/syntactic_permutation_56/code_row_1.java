import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField emailField, newPasswordField, confirmPasswordField, currentPasswordField, newEmailField;
    private JButton loginButton, changeEmailButton;
    private JPanel mainPanel, loginPanel, changeEmailPanel;
    private String loggedInUserEmail = "user@example.com";
    private String loggedInUserPassword = "password";

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new CardLayout());

        mainPanel = new JPanel();
        loginPanel = createLoginPanel();
        changeEmailPanel = createChangeEmailPanel();

        mainPanel.add(loginPanel, "login");
        mainPanel.add(changeEmailPanel, "changeEmail");

        add(mainPanel);

        ((CardLayout) getLayout()).show(mainPanel, "login");
    }

    private JPanel createLoginPanel() {
        JPanel panel = new JPanel(new GridLayout(3, 2));
        JLabel emailLabel = new JLabel("Email:");
        JLabel passwordLabel = new JLabel("Password:");
        emailField = new JTextField();
        currentPasswordField = new JPasswordField();
        loginButton = new JButton("Login");

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (emailField.getText().equals(loggedInUserEmail) && 
                    new String(currentPasswordField.getPassword()).equals(loggedInUserPassword)) {
                    ((CardLayout) mainPanel.getLayout()).show(mainPanel, "changeEmail");
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Invalid email or password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        panel.add(emailLabel);
        panel.add(emailField);
        panel.add(passwordLabel);
        panel.add(currentPasswordField);
        panel.add(new JLabel());
        panel.add(loginButton);

        return panel;
    }

    private JPanel createChangeEmailPanel() {
        JPanel panel = new JPanel(new GridLayout(4, 2));
        JLabel currentPasswordLabel = new JLabel("Current Password:");
        JLabel newEmailLabel = new JLabel("New Email:");
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        currentPasswordField = new JPasswordField();
        newEmailField = new JTextField();
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String currentPassword = new String(currentPasswordField.getPassword());
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!currentPassword.equals(loggedInUserPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (newEmail.isEmpty() || newEmail.equals(loggedInUserEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from the old one and not empty", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!confirmPassword.equals(currentPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Passwords do not match", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    loggedInUserEmail = newEmail;
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                    ((CardLayout) mainPanel.getLayout()).show(mainPanel, "login");
                }
            }
        });

        panel.add(currentPasswordLabel);
        panel.add(currentPasswordField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(new JLabel());
        panel.add(changeEmailButton);

        return panel;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage loginPage = new LoginPage();
            loginPage.setVisible(true);
        });
    }
}