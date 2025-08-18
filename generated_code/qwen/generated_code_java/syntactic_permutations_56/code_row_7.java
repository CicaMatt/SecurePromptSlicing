import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame implements ActionListener {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton loginButton, changeEmailButton;
    private JPanel panel;
    private JLabel oldEmailLabel, newEmailLabel, passwordLabel, confirmPasswordLabel;
    private String currentPassword = "password123"; // Example password
    private String currentEmail = "user@example.com"; // Example email

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2));

        oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        loginButton = new JButton("Login");
        changeEmailButton = new JButton("Change Email");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton);

        loginButton.addActionListener(this);

        add(panel);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == loginButton) {
            String enteredPassword = new String(passwordField.getPassword());
            String enteredEmail = oldEmailField.getText();

            if (enteredEmail.equals(currentEmail) && enteredPassword.equals(currentPassword)) {
                showChangeEmailForm();
            } else {
                JOptionPane.showMessageDialog(this, "Invalid email or password", "Error", JOptionPane.ERROR_MESSAGE);
            }
        } else if (e.getSource() == changeEmailButton) {
            String newEmail = newEmailField.getText();
            String confirmPassword = new String(confirmPasswordField.getPassword());
            String enteredPassword = new String(passwordField.getPassword());

            if (!newEmail.equals(currentEmail)) {
                if (enteredPassword.equals(currentPassword)) {
                    if (confirmPassword.equals(enteredPassword)) {
                        currentEmail = newEmail;
                        JOptionPane.showMessageDialog(this, "Email changed successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                        this.setVisible(false);
                    } else {
                        JOptionPane.showMessageDialog(this, "Passwords do not match", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(this, "Incorrect password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            } else {
                JOptionPane.showMessageDialog(this, "New email must be different from old email", "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private void showChangeEmailForm() {
        panel.removeAll();
        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(this);
        revalidate();
        repaint();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage frame = new LoginPage();
            frame.setVisible(true);
        });
    }
}