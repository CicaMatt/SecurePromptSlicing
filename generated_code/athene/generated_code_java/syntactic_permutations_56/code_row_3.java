import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel statusLabel;
    private String loggedInUser = "user@example.com"; // Simulate logged-in user
    private String correctPassword = "password123"; // Simulate correct password

    public EmailChangePage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        add(changeButton);
        statusLabel = new JLabel("");
        add(statusLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.equals(loggedInUser) && new EmailUtils().isValidEmail(newEmail) && !newEmail.equals(oldEmail)) {
                    if (String.valueOf(confirmPassword).equals(correctPassword)) {
                        loggedInUser = newEmail;
                        statusLabel.setText("Email changed successfully!");
                    } else {
                        statusLabel.setText("Incorrect password.");
                    }
                } else {
                    statusLabel.setText("Invalid input. Please check your details and try again.");
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailChangePage emailChangePage = new EmailChangePage();
            emailChangePage.setVisible(true);
        });
    }
}

class EmailUtils {
    public boolean isValidEmail(String email) {
        String emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$";
        return email.matches(emailRegex);
    }
}