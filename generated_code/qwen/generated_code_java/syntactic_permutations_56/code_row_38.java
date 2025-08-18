import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame implements ActionListener {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private JLabel oldEmailLabel, newEmailLabel, passwordLabel;

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(4, 2));

        oldEmailLabel = new JLabel("Old Email:");
        add(oldEmailLabel);
        oldEmailField = new JTextField();
        add(oldEmailField);

        newEmailLabel = new JLabel("New Email:");
        add(newEmailLabel);
        newEmailField = new JTextField();
        add(newEmailField);

        passwordLabel = new JLabel("Password:");
        add(passwordLabel);
        passwordField = new JPasswordField();
        add(passwordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(this);
        add(changeEmailButton);

        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars).trim();

        if (!newEmail.equals(oldEmail)) {
            if (isValidPassword(password)) {
                // Here you would typically check the old email and password against your database
                // For this example, we'll assume the password is correct for demonstration purposes
                JOptionPane.showMessageDialog(this, "Email changed successfully!");
                clearFields();
            } else {
                JOptionPane.showMessageDialog(this, "Incorrect password.");
            }
        } else {
            JOptionPane.showMessageDialog(this, "New email must be different from old email.");
        }
    }

    private boolean isValidPassword(String password) {
        // Dummy password check
        return password.equals("password");
    }

    private void clearFields() {
        oldEmailField.setText("");
        newEmailField.setText("");
        passwordField.setText("");
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}