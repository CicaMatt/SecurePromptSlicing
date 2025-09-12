import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField passwordField;
    private JButton submitButton;
    private JLabel messageLabel;

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        messageLabel = new JLabel("", SwingConstants.CENTER);
        submitButton = new JButton("Submit");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(new JLabel());
        panel.add(submitButton);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if (oldEmail.isEmpty() || newEmail.isEmpty() || password.isEmpty()) {
                    messageLabel.setText("All fields are required.");
                    return;
                }

                if (!"correctPassword".equals(password)) {
                    messageLabel.setText("Incorrect password.");
                    return;
                }

                if (oldEmail.equals(newEmail)) {
                    messageLabel.setText("New email must be different from old email.");
                    return;
                }

                messageLabel.setText("Email changed successfully!");
            }
        });

        add(panel, BorderLayout.CENTER);
        add(messageLabel, BorderLayout.SOUTH);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            ChangeEmailPage page = new ChangeEmailPage();
            page.setVisible(true);
        });
    }
}