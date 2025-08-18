import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    public LoginPage() {
        setTitle("Change Email");
        setSize(350, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        messageLabel = new JLabel("", SwingConstants.CENTER);

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(messageLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = confirmPasswordField.getPassword();
                String password = new String(passwordChars);

                if (oldEmail.isEmpty() || newEmail.isEmpty() || password.isEmpty()) {
                    messageLabel.setText("All fields are required.");
                } else if (!isValidEmail(oldEmail)) {
                    messageLabel.setText("Invalid old email format.");
                } else if (!isValidEmail(newEmail)) {
                    messageLabel.setText("Invalid new email format.");
                } else if (!isPasswordCorrect(password, oldEmail)) {
                    messageLabel.setText("Incorrect password.");
                } else {
                    changeEmail(oldEmail, newEmail);
                    messageLabel.setText("Email changed successfully.");
                }
            }
        });

        add(panel);
    }

    private boolean isValidEmail(String email) {
        return email.contains("@") && email.contains(".");
    }

    private boolean isPasswordCorrect(String password, String oldEmail) {
        // Placeholder for actual password verification logic
        return "password".equals(password); // This should be replaced with real authentication logic
    }

    private void changeEmail(String oldEmail, String newEmail) {
        // Placeholder for changing email logic
        System.out.println("Changing email from " + oldEmail + " to " + newEmail);
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