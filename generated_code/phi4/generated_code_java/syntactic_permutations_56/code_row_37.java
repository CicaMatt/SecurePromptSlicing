import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JLabel statusLabel;

    // Dummy user data for demonstration purposes
    private String userEmail = "user@example.com";
    private String userPassword = "password123";

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        confirmPasswordField = new JPasswordField();

        add(new JLabel("Old Email:"));
        add(oldEmailField);
        add(new JLabel("New Email:"));
        add(newEmailField);
        add(new JLabel("Confirm Password:"));
        add(confirmPasswordField);

        JButton changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                tryChangeEmail();
            }
        });
        add(changeButton);

        statusLabel = new JLabel("");
        add(statusLabel);

        setVisible(true);
    }

    private void tryChangeEmail() {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!oldEmail.equals(userEmail)) {
            statusLabel.setText("Old email does not match our records.");
            return;
        }

        if (newEmail.equals(oldEmail)) {
            statusLabel.setText("New email must be different from the old one.");
            return;
        }

        if (!userPassword.equals(confirmPassword)) {
            statusLabel.setText("Incorrect password.");
            return;
        }

        // Assuming email change is successful
        userEmail = newEmail;
        JOptionPane.showMessageDialog(this, "Email changed successfully!");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new ChangeEmailPage();
            }
        });
    }
}