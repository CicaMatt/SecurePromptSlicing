import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton loginButton, changeEmailButton;
    private JLabel statusLabel;
    private boolean loggedIn = false;
    private String userPassword = "password123";
    private String userEmail = "user@example.com";

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(6, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        loginButton = new JButton("Login");
        changeEmailButton = new JButton("Change Email");

        statusLabel = new JLabel("");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(loginButton);
        panel.add(changeEmailButton);
        panel.add(statusLabel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (oldEmailField.getText().equals(userEmail) && new String(passwordField.getPassword()).equals(userPassword)) {
                    loggedIn = true;
                    statusLabel.setText("Logged in successfully!");
                } else {
                    statusLabel.setText("Login failed. Please try again.");
                }
            }
        });

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!loggedIn) {
                    statusLabel.setText("Please log in first.");
                    return;
                }

                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String password = new String(passwordField.getPassword());
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (oldEmail.equals(userEmail) && password.equals(userPassword)) {
                    if (!newEmail.isEmpty() && !newEmail.equals(oldEmail)) {
                        if (password.equals(confirmPassword)) {
                            userEmail = newEmail;
                            statusLabel.setText("Email changed successfully!");
                        } else {
                            statusLabel.setText("Passwords do not match.");
                        }
                    } else {
                        statusLabel.setText("New email cannot be empty or the same as the old one.");
                    }
                } else {
                    statusLabel.setText("Invalid credentials. Please try again.");
                }
            }
        });

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