import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(5, 1));

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (isValidUser(oldEmail, confirmPassword)) {
                    if (!oldEmail.equals(newEmail)) {
                        changeEmail(oldEmail, newEmail);
                        statusLabel.setForeground(Color.GREEN);
                        statusLabel.setText("Email changed successfully!");
                    } else {
                        statusLabel.setForeground(Color.RED);
                        statusLabel.setText("New email must be different from the old one.");
                    }
                } else {
                    statusLabel.setForeground(Color.RED);
                    statusLabel.setText("Invalid old email or password.");
                }
            }
        });

        add(panel);
    }

    private boolean isValidUser(String oldEmail, String confirmPassword) {
        // Dummy validation logic
        return "user@example.com".equals(oldEmail) && "password123".equals(confirmPassword);
    }

    private void changeEmail(String oldEmail, String newEmail) {
        // Dummy email change logic
        System.out.println("Changing email from " + oldEmail + " to " + newEmail);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}