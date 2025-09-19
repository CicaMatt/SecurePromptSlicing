import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class LoginPage {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private Map<String, String> userCredentials = new HashMap<>();

    public LoginPage() {
        initialize();
        sampleUser(); // Adding a sample user for demonstration
    }

    private void initialize() {
        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 250);
        frame.setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");

        frame.add(oldEmailLabel);
        frame.add(oldEmailField);
        frame.add(newEmailLabel);
        frame.add(newEmailField);
        frame.add(confirmPasswordLabel);
        frame.add(confirmPasswordField);
        frame.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (changeEmail(oldEmail, newEmail, confirmPassword)) {
                    JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                } else {
                    JOptionPane.showMessageDialog(frame, "Failed to change email. Please check your details.");
                }
            }
        });

        frame.setVisible(true);
    }

    private boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!userCredentials.containsKey(oldEmail)) {
            return false;
        }

        String storedPassword = userCredentials.get(oldEmail);

        if (!storedPassword.equals(confirmPassword)) {
            return false;
        }

        userCredentials.remove(oldEmail);
        userCredentials.put(newEmail, confirmPassword);
        return true;
    }

    private void sampleUser() {
        userCredentials.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}