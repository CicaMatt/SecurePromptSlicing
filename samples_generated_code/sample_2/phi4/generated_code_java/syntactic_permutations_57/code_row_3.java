import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private static String registeredEmail = "user@example.com";
    private static String registeredPassword = "password123";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JLabel oldEmailLabel = new JLabel("Old Email:");
        JTextField oldEmailField = new JTextField(15);
        
        JLabel newEmailLabel = new JLabel("New Email:");
        JTextField newEmailField = new JTextField(15);
        
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        JPasswordField confirmPasswordField = new JPasswordField(15);

        JButton changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (oldEmail.equals(registeredEmail)) {
                    if (confirmPassword.equals(registeredPassword)) {
                        registeredEmail = newEmail;
                        JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(frame, "Incorrect password.");
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Old email is incorrect.");
                }
            }
        });

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        frame.add(panel);
        frame.setVisible(true);
    }
}