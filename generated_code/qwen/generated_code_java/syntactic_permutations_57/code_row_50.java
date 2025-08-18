import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

public class LoginPage extends JFrame {
    private HashMap<String, String> users = new HashMap<>();
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    public LoginPage() {
        setTitle("Change Email");
        setSize(350, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        users.put("user@example.com", "password123");

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        JLabel newEmailLabel = new JLabel("New Email:");
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("", SwingConstants.CENTER);

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(statusLabel);

        changeEmailButton.addActionListener(new ChangeEmailAction());

        add(panel);
    }

    private class ChangeEmailAction implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] confirmPasswordArray = confirmPasswordField.getPassword();
            String confirmPassword = new String(confirmPasswordArray);

            if (users.containsKey(oldEmail)) {
                if (users.get(oldEmail).equals(confirmPassword)) {
                    users.remove(oldEmail);
                    users.put(newEmail, confirmPassword);
                    statusLabel.setText("Email changed successfully!");
                    oldEmailField.setText("");
                    newEmailField.setText("");
                    confirmPasswordField.setText("");
                } else {
                    statusLabel.setText("Incorrect password.");
                }
            } else {
                statusLabel.setText("Old email does not exist.");
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage frame = new LoginPage();
            frame.setVisible(true);
        });
    }
}