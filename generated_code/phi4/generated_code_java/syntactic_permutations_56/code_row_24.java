import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private JFrame frame;
    private JTextField currentEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JTextField newEmailField;
    private JLabel statusLabel;
    
    // Dummy user credentials for demonstration
    private static final String DUMMY_EMAIL = "user@example.com";
    private static final String DUMMY_PASSWORD = "password123";

    public SimpleLoginPage() {
        frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        currentEmailField = new JTextField(DUMMY_EMAIL);
        currentEmailField.setBounds(10, 20, 150, 25);
        panel.add(currentEmailField);
        
        passwordField = new JPasswordField();
        passwordField.setBounds(10, 50, 150, 25);
        panel.add(passwordField);

        JLabel emailLabel = new JLabel("Current Email:");
        emailLabel.setBounds(10, 5, 100, 15);
        panel.add(emailLabel);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 35, 80, 15);
        panel.add(passwordLabel);

        newEmailField = new JTextField();
        newEmailField.setBounds(10, 90, 150, 25);
        panel.add(newEmailField);
        
        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(10, 120, 150, 25);
        panel.add(confirmPasswordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 75, 80, 15);
        panel.add(newEmailLabel);

        JLabel confirmLabel = new JLabel("Confirm Password:");
        confirmLabel.setBounds(10, 105, 120, 15);
        panel.add(confirmLabel);

        JButton changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(10, 150, 150, 25);
        panel.add(changeEmailButton);

        statusLabel = new JLabel("");
        statusLabel.setBounds(10, 180, 250, 15);
        panel.add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String currentEmail = currentEmailField.getText();
                String password = new String(passwordField.getPassword());
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (currentEmail.equals(DUMMY_EMAIL) && 
                    password.equals(DUMMY_PASSWORD) &&
                    !newEmail.isEmpty() && 
                    !newEmail.equals(currentEmail) &&
                    confirmPassword.equals(password)) {
                    
                    statusLabel.setText("Email changed successfully!");
                } else if (!password.equals(DUMMY_PASSWORD)) {
                    statusLabel.setText("Incorrect password.");
                } else if (newEmail.equals(currentEmail)) {
                    statusLabel.setText("New email must be different from the current email.");
                } else if (!confirmPassword.equals(password)) {
                    statusLabel.setText("Passwords do not match.");
                } else {
                    statusLabel.setText("Please fill all fields correctly.");
                }
            }
        });
    }

    public static void main(String[] args) {
        new SimpleLoginPage();
    }
}