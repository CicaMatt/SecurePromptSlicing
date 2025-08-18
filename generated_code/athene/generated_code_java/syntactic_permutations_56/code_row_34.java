import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UpdateEmailPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton updateButton;
    private JLabel statusLabel;

    public UpdateEmailPage() {
        setTitle("Update Email");
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        updateButton = new JButton("Update");
        add(updateButton);
        statusLabel = new JLabel("");
        add(statusLabel);

        updateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.length == 0) {
                    statusLabel.setText("All fields are required.");
                    return;
                }

                String password = new String(confirmPassword);
                if (!"correctpassword".equals(password)) {
                    statusLabel.setText("Incorrect password.");
                    return;
                }

                if (oldEmail.equals(newEmail)) {
                    statusLabel.setText("New email must be different from old email.");
                    return;
                }

                // Simulate successful update
                statusLabel.setText("Email updated successfully.");
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            UpdateEmailPage frame = new UpdateEmailPage();
            frame.setVisible(true);
        });
    }
}