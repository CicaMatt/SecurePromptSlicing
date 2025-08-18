import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel messageLabel;
    private String loggedInUserEmail = "example@example.com";
    private String loggedInUserPassword = "password123";

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        panel.add(oldEmailLabel);
        panel.add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        panel.add(newEmailLabel);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        messageLabel = new JLabel("", SwingConstants.CENTER);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.equals(loggedInUserEmail)) {
                    if (!newEmail.equals(oldEmail)) {
                        if (new String(confirmPassword).equals(loggedInUserPassword)) {
                            loggedInUserEmail = newEmail;
                            messageLabel.setText("Email changed successfully!");
                        } else {
                            messageLabel.setText("Incorrect password.");
                        }
                    } else {
                        messageLabel.setText("New email must be different from old email.");
                    }
                } else {
                    messageLabel.setText("Old email does not match the logged-in user's email.");
                }
            }
        });

        panel.add(changeButton);
        add(panel, BorderLayout.CENTER);
        add(messageLabel, BorderLayout.SOUTH);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new ChangeEmailPage().setVisible(true);
            }
        });
    }
}