import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel resultLabel;
    private String loggedInUserEmail = "user@example.com"; // Example logged-in user
    private String loggedInUserPassword = "password123"; // Example password

    public EmailChangePage() {
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
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        changeButton = new JButton("Change Email");
        resultLabel = new JLabel("");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeButton);
        panel.add(resultLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (oldEmail.equals(loggedInUserEmail) && confirmPassword.equals(loggedInUserPassword)) {
                    loggedInUserEmail = newEmail;
                    resultLabel.setText("Email changed successfully!");
                } else {
                    resultLabel.setText("Incorrect old email or password.");
                }
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailChangePage frame = new EmailChangePage();
            frame.setVisible(true);
        });
    }
}