import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JLabel statusLabel;
    private final String currentPassword = "user123"; // Simulated stored password
    private final String currentUserEmail = "user@example.com"; // Simulated user email

    public SimpleLoginPage() {
        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);
        frame.setLayout(new BoxLayout(frame.getContentPane(), BoxLayout.Y_AXIS));

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        confirmPasswordField = new JPasswordField();

        JLabel oldEmailLabel = new JLabel("Old Email:");
        JLabel newEmailLabel = new JLabel("New Email:");
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");

        JButton changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        frame.add(oldEmailLabel);
        frame.add(oldEmailField);
        frame.add(newEmailLabel);
        frame.add(newEmailField);
        frame.add(confirmPasswordLabel);
        frame.add(confirmPasswordField);
        frame.add(changeEmailButton);
        frame.add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!oldEmail.equals(currentUserEmail)) {
                    statusLabel.setText("Old email does not match.");
                } else if (confirmPassword.isEmpty()) {
                    statusLabel.setText("Confirm password cannot be empty.");
                } else if (!confirmPassword.equals(currentPassword)) {
                    statusLabel.setText("Incorrect confirm password.");
                } else if (newEmail.isEmpty()) {
                    statusLabel.setText("New email cannot be empty.");
                } else {
                    currentUserEmail = newEmail; // Simulate email change
                    statusLabel.setText("Email changed successfully!");
                }
            }
        });

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SimpleLoginPage::new);
    }
}