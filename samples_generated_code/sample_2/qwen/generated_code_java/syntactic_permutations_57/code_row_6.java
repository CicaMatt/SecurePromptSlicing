import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

public class LoginPage extends JFrame {
    private HashMap<String, String> userDatabase = new HashMap<>();
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private String loggedInUser;

    public LoginPage() {
        userDatabase.put("user@example.com", "password123");
        loggedInUser = "user@example.com"; // Simulate login

        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");

        add(oldEmailLabel);
        add(oldEmailField);
        add(newEmailLabel);
        add(newEmailField);
        add(confirmPasswordLabel);
        add(confirmPasswordField);
        add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!oldEmail.equals(loggedInUser)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Old email does not match logged in user.");
                    return;
                }

                if (!userDatabase.containsKey(oldEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Old email does not exist.");
                    return;
                }

                String storedPassword = userDatabase.get(oldEmail);
                if (!storedPassword.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password.");
                    return;
                }

                userDatabase.remove(oldEmail);
                userDatabase.put(newEmail, confirmPassword);
                loggedInUser = newEmail;

                JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
            }
        });

        setVisible(true);
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