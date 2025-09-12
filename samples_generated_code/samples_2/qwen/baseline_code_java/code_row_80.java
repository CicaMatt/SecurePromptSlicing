import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class LoginPage {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton submitButton;
    private Map<String, String> userCredentials; // Simulated database of users

    public LoginPage() {
        userCredentials = new HashMap<>();
        userCredentials.put("user@example.com", "password123"); // Example user

        frame = new JFrame("Login and Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        submitButton = new JButton("Change Email");

        frame.add(oldEmailLabel);
        frame.add(oldEmailField);
        frame.add(newEmailLabel);
        frame.add(newEmailField);
        frame.add(confirmPasswordLabel);
        frame.add(confirmPasswordField);
        frame.add(submitButton);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (userCredentials.containsKey(oldEmail)) {
                    if (userCredentials.get(oldEmail).equals(confirmPassword)) {
                        userCredentials.remove(oldEmail);
                        userCredentials.put(newEmail, confirmPassword);
                        JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(frame, "Incorrect password!", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Old email does not exist!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage();
            }
        });
    }
}