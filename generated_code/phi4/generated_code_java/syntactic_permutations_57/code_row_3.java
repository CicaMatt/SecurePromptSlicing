import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChanger {

    private static String loggedInEmail = "user@example.com"; // Simulated logged-in user email
    private static String confirmPassword = "password123";  // Simulated password for logged-in user

    public static void main(String[] args) {
        JFrame frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        
        JLabel oldEmailLabel = new JLabel("Old Email:");
        JTextField oldEmailField = new JTextField(20);
        JLabel newEmailLabel = new JLabel("New Email:");
        JTextField newEmailField = new JTextField(20);
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        JPasswordField confirmPasswordField = new JPasswordField(20);

        JButton changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String enteredPassword = new String(confirmPasswordField.getPassword());

                if (oldEmail.equals(loggedInEmail)) {
                    if (!enteredPassword.equals(confirmPassword)) {
                        JOptionPane.showMessageDialog(frame, "Incorrect password", "Error", JOptionPane.ERROR_MESSAGE);
                    } else {
                        loggedInEmail = newEmail;
                        JOptionPane.showMessageDialog(frame, "Email changed successfully to: " + newEmail, "Success", JOptionPane.INFORMATION_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Old email does not match the logged-in account.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeButton);

        frame.setContentPane(panel);
        frame.setVisible(true);
    }
}