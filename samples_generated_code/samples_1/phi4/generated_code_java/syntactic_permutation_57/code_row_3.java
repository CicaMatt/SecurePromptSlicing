import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private String currentUserEmail = "user@example.com"; // This should be fetched from a database in real applications
    private String currentPasswordHash = "hashedpassword"; // This should be hashed and stored securely

    public SimpleLoginPage() {
        JFrame frame = new JFrame("Login Page");
        frame.setSize(300, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        oldEmailField = new JTextField(20);
        newEmailField = new JTextField(20);
        confirmPasswordField = new JPasswordField(20);
        changeEmailButton = new JButton("Change Email");

        JPanel panel = new JPanel();
        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (oldEmail.equals(currentUserEmail)) {
                    // Simulate password verification, in a real application use hashed passwords.
                    if (currentPasswordHash.equals(hashPassword(confirmPassword))) {
                        currentUserEmail = newEmail;
                        JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(frame, "Incorrect confirm password.");
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Old email must be the current registered email.");
                }
            }
        });

        panel.add(changeEmailButton);
        frame.add(panel);
        frame.setVisible(true);
    }

    private String hashPassword(String password) {
        // This is a placeholder for password hashing logic.
        return Integer.toString(password.hashCode()); 
    }

    public static void main(String[] args) {
        new SimpleLoginPage();
    }
}