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
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel passwordLabel = new JLabel("Confirm Password:");
        passwordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(new JLabel());
        panel.add(changeEmailButton);

        add(panel);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            String password = new String(passwordField.getPassword());

            if (validateInput(oldEmail, newEmail, password)) {
                if (changeEmail(oldEmail, newEmail, password)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Failed to change email. Please try again.");
                }
            } else {
                JOptionPane.showMessageDialog(LoginPage.this, "Invalid input. Please check your details.");
            }
        }

        private boolean validateInput(String oldEmail, String newEmail, String password) {
            return !oldEmail.isEmpty() && !newEmail.isEmpty() && !password.isEmpty();
        }

        private boolean changeEmail(String oldEmail, String newEmail, String password) {
            // Here you would typically check the database for the old email and password
            // For this example, we'll assume the old email is "user@example.com" and password is "password"
            return "user@example.com".equals(oldEmail) && "password".equals(password);
        }
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