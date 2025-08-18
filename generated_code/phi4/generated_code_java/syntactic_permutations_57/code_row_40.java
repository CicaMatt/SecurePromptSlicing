import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    
    // Simulated user data (for demonstration purposes)
    private String userEmail = "user@example.com";
    private String userPassword = "password123";  // In practice, use hashed passwords

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        
        oldEmailField = new JTextField(20);
        newEmailField = new JTextField(20);
        confirmPasswordField = new JPasswordField(20);
        changeEmailButton = new JButton("Change Email");

        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);

        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);

        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);

        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.equals(userEmail) && new String(confirmPassword).equals(userPassword)) {
                    // Simulating email change
                    userEmail = newEmail;
                    JOptionPane.showMessageDialog(ChangeEmailPage.this, "Email changed successfully!");
                } else {
                    JOptionPane.showMessageDialog(ChangeEmailPage.this, "Invalid credentials or old email.");
                }
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            ChangeEmailPage loginPage = new ChangeEmailPage();
            loginPage.setVisible(true);
        });
    }
}