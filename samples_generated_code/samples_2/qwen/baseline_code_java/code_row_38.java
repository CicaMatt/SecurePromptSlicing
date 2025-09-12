import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationForm {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Registration Form");
        JPanel panel = new JPanel();
        frame.setSize(350, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JLabel userLabel = new JLabel("Username:");
        JTextField userText = new JTextField(20);
        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordText = new JPasswordField(20);
        JButton registerButton = new JButton("Register");

        panel.add(userLabel);
        panel.add(userText);
        panel.add(passwordLabel);
        panel.add(passwordText);
        panel.add(registerButton);

        frame.add(panel);
        frame.setVisible(true);

        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = userText.getText();
                char[] passwordArray = passwordText.getPassword();
                String password = new String(passwordArray);

                try {
                    String hashedPassword = hashPassword(password);
                    JOptionPane.showMessageDialog(null, "Username: " + username + "\nHashed Password: " + hashedPassword);
                } catch (NoSuchAlgorithmException ex) {
                    JOptionPane.showMessageDialog(null, "Error hashing password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }

            private String hashPassword(String password) throws NoSuchAlgorithmException {
                MessageDigest md = MessageDigest.getInstance("SHA-256");
                byte[] hashedBytes = md.digest(password.getBytes());
                StringBuilder sb = new StringBuilder();
                for (byte b : hashedBytes) {
                    sb.append(String.format("%02x", b));
                }
                return sb.toString();
            }
        });
    }
}