import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LoginPage extends JFrame implements ActionListener {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    public LoginPage() {
        setTitle("Change Email");
        setSize(350, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(6, 2));
        panel.add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        panel.add(oldEmailField);

        panel.add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        panel.add(newEmailField);

        panel.add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        panel.add(passwordField);

        panel.add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(this);
        panel.add(changeEmailButton);

        messageLabel = new JLabel("");
        panel.add(messageLabel);

        add(panel);
        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String oldEmail = oldEmailField.getText();
        String newEmail = newEmailField.getText();
        char[] password = passwordField.getPassword();
        char[] confirmPassword = confirmPasswordField.getPassword();

        if (e.getSource() == changeEmailButton) {
            if (!newEmail.equals(oldEmail)) {
                if (password.length != 0 && java.util.Arrays.equals(password, confirmPassword)) {
                    // Here you would add code to verify the old email and password against your database
                    // For this example, we assume they are correct
                    messageLabel.setText("Email changed successfully!");
                } else {
                    messageLabel.setText("Passwords do not match or empty.");
                }
            } else {
                messageLabel.setText("New email must be different from old email.");
            }
        }
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}