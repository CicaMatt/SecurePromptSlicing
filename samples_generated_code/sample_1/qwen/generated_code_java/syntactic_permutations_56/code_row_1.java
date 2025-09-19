import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        JLabel newEmailLabel = new JLabel("New Email:");
        JLabel passwordLabel = new JLabel("Password:");

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        passwordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if (oldEmail.isEmpty() || newEmail.isEmpty() || password.isEmpty()) {
                    JOptionPane.showMessageDialog(LoginPage.this, "All fields must be filled", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!isValidPassword(oldEmail, password)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from old email", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    changeEmail(oldEmail, newEmail);
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });

        add(panel);
    }

    private boolean isValidPassword(String oldEmail, String password) {
        // Dummy validation logic for demonstration purposes
        return oldEmail.equals("user@example.com") && password.equals("password");
    }

    private void changeEmail(String oldEmail, String newEmail) {
        // Logic to change email in the database or storage
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