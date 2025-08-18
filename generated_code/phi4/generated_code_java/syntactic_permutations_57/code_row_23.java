import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private static String currentUserEmail = "user@example.com"; // Simulated logged-in user's email
    private static String userPassword = "password123"; // Simulated password for simplicity

    public static void main(String[] args) {
        JFrame frame = new JFrame("Simple Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel emailLabel = new JLabel("New Email:");
        emailLabel.setBounds(10, 20, 80, 25);
        panel.add(emailLabel);

        JTextField emailTextField = new JTextField(20);
        emailTextField.setBounds(100, 20, 165, 25);
        panel.add(emailTextField);

        JLabel passwordConfirmLabel = new JLabel("Password:");
        passwordConfirmLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordConfirmLabel);

        JPasswordField passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 50, 165, 25);
        panel.add(passwordField);

        JButton changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(10, 80, 150, 25);
        panel.add(changeEmailButton);

        JLabel feedbackLabel = new JLabel("");
        feedbackLabel.setBounds(10, 120, 350, 25);
        panel.add(feedbackLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String newEmail = emailTextField.getText();
                char[] passwordChars = passwordField.getPassword();

                if (newEmail.isEmpty()) {
                    feedbackLabel.setText("New Email cannot be empty.");
                } else if (!String.valueOf(passwordChars).equals(userPassword)) {
                    feedbackLabel.setText("Incorrect password.");
                } else {
                    currentUserEmail = newEmail;
                    feedbackLabel.setText("Email changed successfully to " + currentUserEmail);
                }

                // Clear the password field for security
                passwordField.setText("");
            }
        });
    }
}


This Java code creates a simple GUI application using Swing. It simulates a login scenario where the user can change their email if they are logged in and provide the correct password. The program uses a simulated `currentUserEmail` and `userPassword` to verify the user's identity.