import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class LoginPage extends JFrame {
    private Map<String, String> users = new HashMap<>();
    private JTextField oldEmailField;
    private JPasswordField confirmPasswordField;
    private JTextField newEmailField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Sample user data
        users.put("user@example.com", "password123");

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("", SwingConstants.CENTER);

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(changeEmailButton);
        panel.add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());
                String newEmail = newEmailField.getText();

                if (users.containsKey(oldEmail)) {
                    if (users.get(oldEmail).equals(confirmPassword)) {
                        users.remove(oldEmail);
                        users.put(newEmail, confirmPassword);
                        statusLabel.setText("Email changed successfully!");
                        oldEmailField.setText("");
                        confirmPasswordField.setText("");
                        newEmailField.setText("");
                    } else {
                        statusLabel.setText("Incorrect password.");
                    }
                } else {
                    statusLabel.setText("Old email not found.");
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