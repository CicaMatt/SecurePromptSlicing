import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeApp extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel statusLabel;

    public EmailChangeApp() {
        setTitle("Change Email");
        setSize(300, 200);
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

        changeButton = new JButton("Change Email");
        add(changeButton);
        statusLabel = new JLabel("");
        add(statusLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (isValidUser(oldEmail, confirmPassword)) {
                    changeEmail(oldEmail, newEmail);
                    statusLabel.setText("Email changed successfully.");
                } else {
                    statusLabel.setText("Incorrect email or password.");
                }
            }
        });
    }

    private boolean isValidUser(String oldEmail, char[] confirmPassword) {
        // Dummy validation logic
        String correctPassword = "password123"; // Replace with actual password retrieval logic
        return "user@example.com".equals(oldEmail) && new String(confirmPassword).equals(correctPassword);
    }

    private void changeEmail(String oldEmail, String newEmail) {
        // Logic to update the email in the database or backend system
        System.out.println("Changing email from " + oldEmail + " to " + newEmail);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new EmailChangeApp().setVisible(true);
            }
        });
    }
}