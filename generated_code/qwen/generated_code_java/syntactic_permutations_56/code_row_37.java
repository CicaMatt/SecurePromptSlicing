import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame implements ActionListener {

    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private String loggedInUserEmail = "user@example.com"; // Simulated logged-in user email
    private String loggedInUserPassword = "password123"; // Simulated logged-in user password

    public LoginPage() {
        setTitle("Change Email");
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        add(oldEmailLabel);
        oldEmailField = new JTextField();
        add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        add(newEmailLabel);
        newEmailField = new JTextField();
        add(newEmailField);

        JLabel passwordLabel = new JLabel("Confirm Password:");
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
        String password = new String(passwordChars);

        if (!oldEmail.equals(loggedInUserEmail)) {
            JOptionPane.showMessageDialog(this, "Old email does not match logged in user's email.", "Error", JOptionPane.ERROR_MESSAGE);
        } else if (newEmail.equals(oldEmail)) {
            JOptionPane.showMessageDialog(this, "New email must be different from the old email.", "Error", JOptionPane.ERROR_MESSAGE);
        } else if (!password.equals(loggedInUserPassword)) {
            JOptionPane.showMessageDialog(this, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
        } else {
            loggedInUserEmail = newEmail;
            JOptionPane.showMessageDialog(this, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(LoginPage::new);
    }
}