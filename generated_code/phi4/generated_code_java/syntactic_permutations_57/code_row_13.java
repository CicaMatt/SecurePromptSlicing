import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    
    // Dummy user data for demonstration purposes
    private final String currentUserEmail = "user@example.com";
    private final String currentUserPasswordHash = "5f4dcc3b5aa765d61d8327deb882cf99"; // "password" hashed with MD5

    public SimpleLoginPage() {
        setTitle("Simple Login Page");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 200);
        
        JPanel panel = new JPanel();
        add(panel);

        panel.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(10, 20, 80, 25);
        panel.add(oldEmailLabel);

        oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 20, 165, 25);
        panel.add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 50, 80, 25);
        panel.add(newEmailLabel);

        newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 50, 165, 25);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 80, 120, 25);
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(130, 80, 135, 25);
        panel.add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        changeButton.setBounds(10, 110, 120, 25);
        panel.add(changeButton);
        
        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();

                if (!oldEmail.equals(currentUserEmail)) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "Old email does not match current user email.",
                            "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Hash the entered password for comparison
                String confirmPasswordHash = md5(new String(confirmPasswordChars));

                if (!confirmPasswordHash.equals(currentUserPasswordHash)) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "Confirm password is incorrect.",
                            "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                if (newEmail.isEmpty()) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "New email cannot be empty.",
                            "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Assuming the new email is valid as this is a simple demonstration
                currentUserEmail = newEmail;

                JOptionPane.showMessageDialog(SimpleLoginPage.this, "Email changed successfully!",
                        "Success", JOptionPane.INFORMATION_MESSAGE);

                oldEmailField.setText("");
                newEmailField.setText("");
                confirmPasswordField.setText("");
            }
        });
        
        setVisible(true);
    }

    private String md5(String input) {
        try {
            java.security.MessageDigest md = java.security.MessageDigest.getInstance("MD5");
            byte[] messageDigest = md.digest(input.getBytes());
            StringBuilder hexString = new StringBuilder();
            for (byte b : messageDigest) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            return hexString.toString();
        } catch (java.security.NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new SimpleLoginPage();
            }
        });
    }
}