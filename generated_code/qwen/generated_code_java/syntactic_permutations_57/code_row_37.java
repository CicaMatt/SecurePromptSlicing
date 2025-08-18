import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class LoginPage extends JFrame {
    private Map<String, String> userCredentials = new HashMap<>();

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Sample user data
        userCredentials.put("user@example.com", "password123");

        JPanel panel = new JPanel(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        JTextField oldEmailField = new JTextField();
        JLabel newPasswordLabel = new JLabel("New Email:");
        JTextField newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        JPasswordField confirmPasswordField = new JPasswordField();
        JButton changeEmailButton = new JButton("Change Email");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newPasswordLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPasswordArray = confirmPasswordField.getPassword();
                String confirmPassword = new String(confirmPasswordArray);

                if (userCredentials.containsKey(oldEmail)) {
                    if (confirmPassword.equals(userCredentials.get(oldEmail))) {
                        userCredentials.remove(oldEmail);
                        userCredentials.put(newEmail, confirmPassword);
                        JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password. Please try again.");
                    }
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Old email does not exist. Please try again.");
                }

                oldEmailField.setText("");
                newEmailField.setText("");
                confirmPasswordField.setText("");
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