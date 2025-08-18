import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeApp {

    private static String userEmail = "user@example.com";
    private static String userPassword = "password123";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Email Change");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JTextField oldEmailField = new JTextField(20);
        JTextField newEmailField = new JTextField(20);
        JPasswordField passwordField = new JPasswordField(20);
        JButton changeEmailButton = new JButton("Change Email");

        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String password = new String(passwordField.getPassword());

                if (userEmail.equals(oldEmail)) {
                    if (password.equals(userPassword)) {
                        if (!newEmail.isEmpty() && !newEmail.equals(oldEmail)) {
                            userEmail = newEmail;
                            JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                        } else {
                            JOptionPane.showMessageDialog(frame, "New email must be different from the old one.");
                        }
                    } else {
                        JOptionPane.showMessageDialog(frame, "Incorrect password.");
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Old email does not match our records.");
                }
            }
        });

        frame.add(panel);
        frame.setVisible(true);
    }
}