import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RegistrationForm extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton registerButton;

    public RegistrationForm() {
        createUI();
    }

    private void createUI() {
        setTitle("Registration Form");
        setSize(300, 200);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        panel.add(new JLabel("Username:"));
        usernameField = new JTextField(15);
        panel.add(usernameField);

        panel.add(new JLabel("Password:"));
        passwordField = new JPasswordField(15);
        panel.add(passwordField);

        registerButton = new JButton("Register");
        panel.add(registerButton);

        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordChars = passwordField.getPassword();

                if (username.isEmpty() || passwordChars.length == 0) {
                    JOptionPane.showMessageDialog(null, "Username and Password cannot be empty");
                } else {
                    try {
                        registerUser(username, new String(passwordChars));
                        JOptionPane.showMessageDialog(null, "Registration successful!");
                    } catch (Exception ex) {
                        ex.printStackTrace();
                        JOptionPane.showMessageDialog(null, "Error during registration: " + ex.getMessage());
                    }
                }
            }
        });
    }

    private void registerUser(String username, String password) throws NoSuchAlgorithmException, SQLException {
        SecureRandom random = new SecureRandom();
        byte[] saltBytes = new byte[16];
        random.nextBytes(saltBytes);
        String salt = bytesToHex(saltBytes);

        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt.getBytes());
        byte[] hashedPassword = md.digest(password.getBytes());

        String storedPassword = bytesToHex(hashedPassword) + ":" + salt;

        try (Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/mydatabase", "root", "password")) {
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
            stmt.setString(1, username);
            stmt.setString(2, storedPassword);

            stmt.executeUpdate();
        }
    }

    private String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            RegistrationForm frame = new RegistrationForm();
            frame.setVisible(true);
        });
    }
}