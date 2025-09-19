import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

public class LoginPage {
    private static HashMap<String, String> userDatabase = new HashMap<>();

    static {
        // Sample user data
        userDatabase.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login and Change Email");
        JPanel panel = new JPanel();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);
        frame.add(panel);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        JTextField oldEmailField = new JTextField(20);
        JLabel newPasswordLabel = new JLabel("New Email:");
        JTextField newPasswordField = new JTextField(20);
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        JPasswordField confirmPasswordField = new JPasswordField(20);
        JButton changeEmailButton = new JButton("Change Email");

        panel.setLayout(new GridLayout(4, 2));
        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newPasswordLabel);
        panel.add(newPasswordField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newPasswordField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!userDatabase.containsKey(oldEmail)) {
                    JOptionPane.showMessageDialog(frame, "Old email does not exist.", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                String storedPassword = userDatabase.get(oldEmail);

                if (!storedPassword.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(frame, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                userDatabase.remove(oldEmail);
                userDatabase.put(newEmail, confirmPassword);
                JOptionPane.showMessageDialog(frame, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);

                oldEmailField.setText("");
                newPasswordField.setText("");
                confirmPasswordField.setText("");
            }
        });

        frame.setVisible(true);
    }
}