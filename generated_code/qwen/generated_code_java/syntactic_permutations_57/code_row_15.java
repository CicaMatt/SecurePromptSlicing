import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

public class LoginPage extends JFrame {
    private HashMap<String, String> users = new HashMap<>();

    public LoginPage() {
        users.put("oldemail@example.com", "password123"); // Example user

        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        JTextField oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        JTextField newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        JPasswordField confirmPasswordField = new JPasswordField();

        JButton changeButton = new JButton("Change Email");
        JLabel messageLabel = new JLabel("", SwingConstants.CENTER);

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(new JLabel()); // Empty label for spacing
        panel.add(changeButton);
        panel.add(messageLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = confirmPasswordField.getPassword();
                String confirmPassword = new String(passwordChars);

                if (users.containsKey(oldEmail)) {
                    if (users.get(oldEmail).equals(confirmPassword)) {
                        users.remove(oldEmail);
                        users.put(newEmail, confirmPassword);
                        messageLabel.setForeground(Color.GREEN);
                        messageLabel.setText("Email changed successfully!");
                    } else {
                        messageLabel.setForeground(Color.RED);
                        messageLabel.setText("Incorrect password!");
                    }
                } else {
                    messageLabel.setForeground(Color.RED);
                    messageLabel.setText("Old email does not exist!");
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