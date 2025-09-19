import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private String userOldEmail = "user@example.com";
    private String userPassword = "password";

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");

        add(oldEmailLabel);
        add(oldEmailField);
        add(newEmailLabel);
        add(newEmailField);
        add(passwordLabel);
        add(passwordField);
        add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if (oldEmail.equals(userOldEmail) && password.equals(userPassword)) {
                    if (!newEmail.equals(oldEmail)) {
                        JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
                        userOldEmail = newEmail;
                    } else {
                        JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from old email.");
                    }
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect old email or password.");
                }
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