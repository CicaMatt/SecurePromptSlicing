import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeForm extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton submitButton;
    private JLabel statusLabel;

    public EmailChangeForm() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        panel.add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        panel.add(oldEmailField);

        panel.add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        panel.add(newEmailField);

        panel.add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordField);

        submitButton = new JButton("Submit");
        panel.add(submitButton);
        statusLabel = new JLabel("");
        panel.add(statusLabel);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.length == 0) {
                    statusLabel.setText("All fields are required.");
                    return;
                }

                if (!isPasswordCorrect(new String(confirmPassword))) {
                    statusLabel.setText("Incorrect password.");
                    return;
                }

                if (oldEmail.equals(newEmail)) {
                    statusLabel.setText("New email must be different from old email.");
                    return;
                }

                // Simulate successful change
                statusLabel.setText("Email changed successfully!");
            }
        });

        add(panel);
    }

    private boolean isPasswordCorrect(String password) {
        // Dummy implementation for demonstration purposes
        return "password123".equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailChangeForm form = new EmailChangeForm();
            form.setVisible(true);
        });
    }
}