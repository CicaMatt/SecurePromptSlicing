import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage {

    private static boolean isLoggedIn = true; // Simulate user login status
    private static String userEmail = "user@example.com"; // User's current email
    private static String userPassword = "password123"; // User's password

    public static void main(String[] args) {
        JFrame frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);
        
        JLabel oldEmailLabel = new JLabel("Old Email:");
        JTextField oldEmailField = new JTextField(20);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        JPasswordField confirmPasswordField = new JPasswordField(20);

        JLabel newEmailLabel = new JLabel("New Email:");
        JTextField newEmailField = new JTextField(20);
        
        JButton changeButton = new JButton("Change Email");

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));
        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();
                String newEmail = newEmailField.getText();

                if (isLoggedIn && oldEmail.equals(userEmail)
                        && String.valueOf(confirmPassword).equals(userPassword)) {

                    JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                    userEmail = newEmail;
                } else {
                    JOptionPane.showMessageDialog(frame,
                            "Invalid credentials or not logged in!",
                            "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        panel.add(changeButton);

        frame.add(panel);
        frame.setVisible(true);
    }
}