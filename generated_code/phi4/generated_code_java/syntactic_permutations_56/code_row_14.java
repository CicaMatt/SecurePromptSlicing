import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginAndChangeEmail {
    private static String currentEmail = "user@example.com";
    private static String password = "password123";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login and Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JTextField oldEmailField = new JTextField(20);
        JTextField newEmailField = new JTextField(20);
        JPasswordField confirmPasswordField = new JPasswordField(20);
        JLabel passwordLabel = new JLabel("Enter Password:");
        JLabel oldEmailLabel = new JLabel("Old Email:");
        JLabel newEmailLabel = new JLabel("New Email:");
        JLabel confirmLabel = new JLabel("Confirm Password:");

        JButton submitButton = new JButton("Change Email");
        
        panel.add(passwordLabel);
        panel.add(new JPasswordField(20));
        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmLabel);
        panel.add(confirmPasswordField);
        panel.add(submitButton);

        frame.add(panel);
        frame.setVisible(true);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = ((JPasswordField) panel.getComponent(1)).getPassword();
                String enteredPassword = new String(passwordChars);

                if (!currentEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(frame, "Old email does not match.");
                    return;
                }
                
                if (enteredPassword.isEmpty() || !enteredPassword.equals(password)) {
                    JOptionPane.showMessageDialog(frame, "Incorrect password.");
                    return;
                }

                if (newEmail.equals(currentEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from the current one.");
                    return;
                }

                currentEmail = newEmail; // Update email
                JOptionPane.showMessageDialog(frame, "Email changed successfully!");
            }
        });
    }
}