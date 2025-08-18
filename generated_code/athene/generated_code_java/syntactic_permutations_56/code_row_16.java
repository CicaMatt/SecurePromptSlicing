import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel statusLabel;

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
        statusLabel = new JLabel("");

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.length == 0) {
                    statusLabel.setText("All fields are required.");
                } else if (oldEmail.equals(newEmail)) {
                    statusLabel.setText("New email must be different from old email.");
                } else if (!"yourPasswordHere".equals(new String(confirmPassword))) {
                    statusLabel.setText("Incorrect password.");
                } else {
                    // Simulate email change
                    statusLabel.setText("Email changed successfully!");
                    oldEmailField.setText("");
                    newEmailField.setText("");
                    confirmPasswordField.setText("");
                }
            }
        });

        panel.add(changeButton);
        panel.add(statusLabel);

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