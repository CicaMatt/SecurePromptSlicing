import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage extends JFrame {
    private JTextField emailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;
    private String currentEmail = "user@example.com";
    private String correctPassword = "password123";

    public EmailChangePage() {
        setTitle("Change Email");
        setSize(400, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

        JLabel emailLabel = new JLabel("New Email:");
        emailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        panel.add(emailLabel);
        panel.add(emailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);
        panel.add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String newEmail = emailField.getText();
                char[] enteredPassword = confirmPasswordField.getPassword();

                if (newEmail.isEmpty() || enteredPassword.length == 0) {
                    statusLabel.setText("Please fill in all fields.");
                } else if (newEmail.equals(currentEmail)) {
                    statusLabel.setText("New email must be different from the current one.");
                } else if (!String.valueOf(enteredPassword).equals(correctPassword)) {
                    statusLabel.setText("Incorrect password.");
                } else {
                    currentEmail = newEmail;
                    statusLabel.setText("Email changed successfully!");
                }
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new EmailChangePage().setVisible(true);
            }
        });
    }
}