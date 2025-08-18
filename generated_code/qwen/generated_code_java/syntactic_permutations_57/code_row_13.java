import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    private String storedEmail = "user@example.com";
    private String storedPassword = "password123";

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        oldEmailField = new JTextField();
        oldEmailField.setText("Old Email");

        newEmailField = new JTextField();
        newEmailField.setText("New Email");

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setText("Confirm Password");

        changeEmailButton = new JButton("Change Email");
        messageLabel = new JLabel("");

        panel.add(oldEmailField);
        panel.add(newEmailField);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(messageLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (oldEmail.equals(storedEmail) && confirmPassword.equals(storedPassword)) {
                    storedEmail = newEmail;
                    messageLabel.setText("Email changed successfully!");
                } else {
                    messageLabel.setText("Invalid old email or confirm password.");
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