import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class UpdateEmailPage extends JFrame implements ActionListener {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton updateButton;
    private JLabel messageLabel;

    public UpdateEmailPage() {
        setTitle("Update Email");
        setSize(400, 350);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        updateButton = new JButton("Update");
        messageLabel = new JLabel("");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(updateButton);
        panel.add(messageLabel);

        updateButton.addActionListener(this);

        add(panel);
    }

    public void actionPerformed(ActionEvent e) {
        String oldEmail = oldEmailField.getText();
        String newEmail = newEmailField.getText();
        String password = new String(passwordField.getPassword());
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!password.equals("correctPassword")) { // Replace "correctPassword" with actual validation
            messageLabel.setText("Incorrect Password");
        } else if (oldEmail.isEmpty() || newEmail.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
            messageLabel.setText("All fields are required");
        } else if (!newEmail.equals(confirmPassword)) {
            messageLabel.setText("New email and confirm email do not match");
        } else if (oldEmail.equals(newEmail)) {
            messageLabel.setText("New email must be different from old email");
        } else {
            messageLabel.setText("Email updated successfully!");
            // Here you would add code to update the email in your database
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            UpdateEmailPage frame = new UpdateEmailPage();
            frame.setVisible(true);
        });
    }
}