import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    // Dummy user data for demonstration purposes
    private final String DUMMY_EMAIL = "user@example.com";
    private final String DUMMY_PASSWORD = "password123";

    public LoginPage() {
        setTitle("Change Email");
        setSize(350, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(6, 2));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        messageLabel = new JLabel("");
        add(messageLabel);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());
        add(changeEmailButton);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            String confirmPassword = new String(confirmPasswordField.getPassword());

            if (DUMMY_EMAIL.equals(oldEmail)) {
                if (DUMMY_PASSWORD.equals(confirmPassword)) {
                    // Here you would update the user's email in your database
                    messageLabel.setText("Email changed successfully!");
                    oldEmailField.setText("");
                    newEmailField.setText("");
                    confirmPasswordField.setText("");
                } else {
                    messageLabel.setText("Incorrect password.");
                }
            } else {
                messageLabel.setText("Old email does not match our records.");
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