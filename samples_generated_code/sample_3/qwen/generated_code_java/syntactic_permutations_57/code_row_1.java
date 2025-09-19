import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

public class LoginPage {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton loginButton, changeEmailButton;
    private JLabel statusLabel;
    private HashMap<String, String> userCredentials; // Simple in-memory database

    public LoginPage() {
        userCredentials = new HashMap<>();
        userCredentials.put("user@example.com", "password123"); // Sample user data

        frame = new JFrame("Login and Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);
        frame.setLayout(new GridLayout(6, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        loginButton = new JButton("Login");
        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("", SwingConstants.CENTER);

        frame.add(oldEmailLabel);
        frame.add(oldEmailField);
        frame.add(newEmailLabel);
        frame.add(newEmailField);
        frame.add(confirmPasswordLabel);
        frame.add(confirmPasswordField);
        frame.add(loginButton);
        frame.add(changeEmailButton);
        frame.add(statusLabel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String password = new String(confirmPasswordField.getPassword());
                if (userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
                    changeEmailButton.setEnabled(true);
                    statusLabel.setText("Logged in successfully.");
                } else {
                    statusLabel.setText("Invalid credentials. Please try again.");
                }
            }
        });

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String password = new String(confirmPasswordField.getPassword());

                if (userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
                    if (!newEmail.isEmpty()) {
                        userCredentials.remove(oldEmail);
                        userCredentials.put(newEmail, password);
                        statusLabel.setText("Email changed successfully.");
                        oldEmailField.setText("");
                        newEmailField.setText("");
                        confirmPasswordField.setText("");
                        changeEmailButton.setEnabled(false);
                    } else {
                        statusLabel.setText("New email cannot be empty.");
                    }
                } else {
                    statusLabel.setText("Incorrect old email or password.");
                }
            }
        });

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage();
            }
        });
    }
}