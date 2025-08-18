import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private String currentEmail = "user@example.com"; // This should be fetched from user session or database
    private String correctPassword = "password123";   // This should be securely stored and verified

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        
        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField(20);
        panel.add(oldEmailLabel);
        panel.add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField(20);
        panel.add(newEmailLabel);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField(20);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        panel.add(changeButton);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                char[] passwordChars = confirmPasswordField.getPassword();
                String password = new String(passwordChars);
                
                if (!oldEmail.equals(currentEmail)) {
                    JOptionPane.showMessageDialog(null, "Old email does not match.");
                    return;
                }
                
                if (!password.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(null, "Incorrect password.");
                    return;
                }

                if (oldEmail.equals(newEmailField.getText())) {
                    JOptionPane.showMessageDialog(null, "New email must be different from old email.");
                    return;
                }

                // Here you should update the user's email in your database
                currentEmail = newEmailField.getText();
                
                JOptionPane.showMessageDialog(null, "Email changed successfully!");
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            ChangeEmailPage frame = new ChangeEmailPage();
            frame.setVisible(true);
        });
    }
}