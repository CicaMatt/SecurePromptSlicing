import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class LoginPage extends JFrame {
    private Map<String, String> userCredentials = new HashMap<>();
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel messageLabel;

    public LoginPage() {
        setTitle("Change Email");
        setSize(350, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        userCredentials.put("user@example.com", "password123");

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");
        messageLabel = new JLabel("");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(messageLabel);

        changeEmailButton.addActionListener(new ChangeEmailListener());

        add(panel);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            String confirmPassword = new String(confirmPasswordField.getPassword());

            if (!userCredentials.containsKey(oldEmail)) {
                messageLabel.setText("Old email does not exist.");
                return;
            }

            if (!userCredentials.get(oldEmail).equals(confirmPassword)) {
                messageLabel.setText("Incorrect password.");
                return;
            }

            userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, confirmPassword);
            messageLabel.setText("Email changed successfully.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage frame = new LoginPage();
            frame.setVisible(true);
        });
    }
}