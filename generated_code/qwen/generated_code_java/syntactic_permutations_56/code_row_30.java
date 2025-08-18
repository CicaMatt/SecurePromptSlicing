import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private String loggedInUserOldEmail = "user@example.com"; // Example logged in user's email
    private String loggedInUserPassword = "password123"; // Example logged in user's password

    public LoginPage() {
        setTitle("Change Email");
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(changeEmailButton);

        add(panel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if (!oldEmail.equals(loggedInUserOldEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect old email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from the old email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!password.equals(loggedInUserPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Here you would typically update the user's email in a database
                    loggedInUserOldEmail = newEmail;
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                    dispose();
                }
            }
        });
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