import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RegistrationForm extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton registerButton;

    public RegistrationForm() {
        setTitle("Registration Form");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 1));

        JLabel usernameLabel = new JLabel("Username:");
        usernameField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        registerButton = new JButton("Register");
        registerButton.addActionListener(new RegisterButtonListener());

        panel.add(usernameLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(registerButton);

        add(panel);
    }

    private class RegisterButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String username = usernameField.getText();
            char[] passwordChars = passwordField.getPassword();
            String password = new String(passwordChars);

            if (!username.isEmpty() && !password.isEmpty()) {
                try {
                    byte[] salt = generateSalt();
                    byte[] hashedPassword = hashPassword(password, salt);
                    storeUser(username, hashedPassword, salt);
                    JOptionPane.showMessageDialog(null, "Registration Successful!");
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(null, "Error during registration: " + ex.getMessage());
                }
            } else {
                JOptionPane.showMessageDialog(null, "Please fill in all fields.");
            }
        }

        private byte[] generateSalt() {
            SecureRandom random = new SecureRandom();
            byte[] salt = new byte[16];
            random.nextBytes(salt);
            return salt;
        }

        private byte[] hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
            MessageDigest md = MessageDigest.getInstance("SHA-512");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());
            return hashedPassword;
        }

        private void storeUser(String username, byte[] hashedPassword, byte[] salt) throws Exception {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String dbUsername = "root";
            String dbPassword = "";

            try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword)) {
                String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
                try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                    preparedStatement.setString(1, username);
                    preparedStatement.setBytes(2, hashedPassword);
                    preparedStatement.setBytes(3, salt);
                    preparedStatement.executeUpdate();
                }
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new RegistrationForm().setVisible(true));
    }
}



CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password BINARY(64) NOT NULL,
    salt BINARY(16) NOT NULL
);