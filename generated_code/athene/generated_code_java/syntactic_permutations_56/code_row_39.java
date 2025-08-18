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

    public EmailChangePage() {
        setTitle("Change Email");
        setSize(400, 250);
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

        changeButton = new JButton("Change Email");
        resultLabel = new JLabel("");

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (isValid(oldEmail, newEmail, confirmPassword)) {
                    resultLabel.setText("Email changed successfully!");
                } else {
                    resultLabel.setText("Failed to change email. Please check your inputs.");
                }
            }

            private boolean isValid(String oldEmail, String newEmail, char[] confirmPassword) {
                // Simulate authentication
                String correctPassword = "password123"; // Replace with actual password retrieval logic
                return oldEmail.length() > 0 && newEmail.length() > 0 && new String(confirmPassword).equals(correctPassword);
            }
        });

        panel.add(changeButton);
        panel.add(resultLabel);

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailChangePage frame = new EmailChangePage();
            frame.setVisible(true);
        });
    }
}