import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private String correctOldEmail = "user@example.com";
    private String correctPassword = "password";

    public LoginPage() {
        setTitle("Login and Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        getContentPane().add(panel);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        panel.add(oldEmailLabel);

        oldEmailField = new JTextField(20);
        panel.add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        panel.add(newEmailLabel);

        newEmailField = new JTextField(20);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        panel.add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();
                String confirmPassword = new String(confirmPasswordChars);

                if (oldEmail.equals(correctOldEmail) && confirmPassword.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(null, "Email changed successfully to: " + newEmail);
                    oldEmailField.setText(newEmail);
                } else {
                    JOptionPane.showMessageDialog(null, "Invalid old email or password.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}