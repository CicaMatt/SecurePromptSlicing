import java.util.HashMap;
import java.util.Map;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private static Map<String, String> users = new HashMap<>();
    
    // Sample user data for demonstration purposes
    static {
        users.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login and Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        
        JLabel oldEmailLabel = new JLabel("Old Email:");
        JTextField oldEmailField = new JTextField(20);
        JLabel newEmailLabel = new JLabel("New Email:");
        JTextField newEmailField = new JTextField(20);
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        JPasswordField confirmPasswordField = new JPasswordField(20);

        JButton changeEmailButton = new JButton("Change Email");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!users.containsKey(oldEmail)) {
                    JOptionPane.showMessageDialog(frame, "Old email does not exist.");
                } else if (!users.get(oldEmail).equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(frame, "Confirm password is incorrect.");
                } else if (users.containsKey(newEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email already exists.");
                } else {
                    users.remove(oldEmail);
                    users.put(newEmail, confirmPassword);
                    JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                }
            }
        });

        frame.add(panel);
        frame.setVisible(true);
    }
}