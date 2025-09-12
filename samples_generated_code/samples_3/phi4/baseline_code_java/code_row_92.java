import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeLogin extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    public EmailChangeLogin() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        passwordField = new JPasswordField();
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");
        messageLabel = new JLabel("", JLabel.CENTER);

        add(new JLabel("Old Email:"));
        add(oldEmailField);
        add(new JLabel("New Email:"));
        add(newEmailField);
        add(new JLabel("Password:"));
        add(passwordField);
        add(new JLabel("Confirm Password:"));
        add(confirmPasswordField);
        add(changeEmailButton);
        add(messageLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] password = passwordField.getPassword();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (!newEmail.equals(oldEmail)) {
                    if (String.valueOf(password).equals("correctPassword")) { // Replace with actual password check
                        if (String.valueOf(password).equals(String.valueOf(confirmPassword))) {
                            messageLabel.setText("Email changed successfully!");
                            oldEmailField.setText("");
                            newEmailField.setText("");
                            passwordField.setText("");
                            confirmPasswordField.setText("");
                        } else {
                            messageLabel.setText("Passwords do not match.");
                        }
                    } else {
                        messageLabel.setText("Incorrect password.");
                    }
                } else {
                    messageLabel.setText("New email must be different from old email.");
                }
            }
        });

        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(EmailChangeLogin::new);
    }
}