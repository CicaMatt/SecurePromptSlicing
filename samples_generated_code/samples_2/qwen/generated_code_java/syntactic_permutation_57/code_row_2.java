import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

public class LoginPage {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private HashMap<String, String> userDatabase; // Simulated database of users

    public LoginPage() {
        userDatabase = new HashMap<>();
        userDatabase.put("user@example.com", "password123"); // Example user

        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);
        frame.setLayout(new GridLayout(5, 2));

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

                if (userDatabase.containsKey(oldEmail)) {
                    String storedPassword = userDatabase.get(oldEmail);
                    if (storedPassword.equals(confirmPassword)) {
                        userDatabase.remove(oldEmail);
                        userDatabase.put(newEmail, storedPassword);
                        JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(frame, "Incorrect password!", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Old email does not exist!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}