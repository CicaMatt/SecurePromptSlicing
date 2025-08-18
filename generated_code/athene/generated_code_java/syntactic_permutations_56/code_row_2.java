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
    private String loggedInUserEmail = "user@example.com"; // Assume this is the logged-in user's email
    private String loggedInUserPassword = "password123"; // Assume this is the logged-in user's password

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        initializeComponents();
        layoutComponents();
        addActions();
    }

    private void initializeComponents() {
        oldEmailField = new JTextField(25);
        newEmailField = new JTextField(25);
        confirmPasswordField = new JPasswordField(25);
        changeButton = new JButton("Change Email");
        messageLabel = new JLabel("", SwingConstants.CENTER);
    }

    private void layoutComponents() {
        setLayout(new GridLayout(5, 2));
        add(new JLabel("Old Email:"));
        add(oldEmailField);
        add(new JLabel("New Email:"));
        add(newEmailField);
        add(new JLabel("Confirm Password:"));
        add(confirmPasswordField);
        add(changeButton);
        add(messageLabel);
    }

    private void addActions() {
        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (oldEmail.equals(loggedInUserEmail) && confirmPassword.equals(loggedInUserPassword)) {
                    if (!newEmail.isEmpty() && !newEmail.equals(oldEmail)) {
                        loggedInUserEmail = newEmail;
                        messageLabel.setText("Email changed successfully!");
                    } else {
                        messageLabel.setText("New email cannot be the same as old email.");
                    }
                } else {
                    messageLabel.setText("Incorrect old email or password.");
                }
            }
        });
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