import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmPasswordField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private String loggedInUserEmail = "user@example.com";
    private String loggedInUserPassword = "password123";

    public LoginPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JTextField();

        changeEmailButton = new JButton("Change Email");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String password = new String(passwordField.getPassword());
                String newEmail = newEmailField.getText();
                String confirmPassword = confirmPasswordField.getText();

                if (!oldEmail.equals(loggedInUserEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Old email does not match.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!password.equals(loggedInUserPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!newEmail.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email and confirm password do not match.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!isValidEmail(newEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Please enter a valid email address.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    loggedInUserEmail = newEmail;
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully.", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });

        add(panel);
    }

    private boolean isValidEmail(String email) {
        return email.matches("^[A-Za-z0-9+_.-]+@(.+)$");
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