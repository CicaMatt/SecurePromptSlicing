import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.security.SecureRandom;
import java.security.NoSuchAlgorithmException;
import java.math.BigInteger;

import javax.swing.*;
import java.awt.event.*;

public class RegistrationForm extends JFrame {
    private JTextField usernameField = new JTextField(20);
    private JPasswordField passwordField = new JPasswordField(20);
    private JButton registerButton = new JButton("Register");

    public RegistrationForm() {
        super("Registration Form");
        setLayout(null);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setBounds(10, 10, 80, 25);
        add(usernameLabel);

        usernameField.setBounds(100, 10, 160, 25);
        add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 40, 80, 25);
        add(passwordLabel);

        passwordField.setBounds(100, 40, 160, 25);
        add(passwordField);

        registerButton.setBounds(10, 80, 160, 25);
        add(registerButton);

        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if (!username.isEmpty() && !password.isEmpty()) {
                    try {
                        byte[] salt = generateSalt();
                        String hashedPassword = hashPassword(password, salt);
                        storeUser(username, hashedPassword, salt);
                        JOptionPane.showMessageDialog(null, "Registration Successful!");
                    } catch (Exception ex) {
                        JOptionPane.showMessageDialog(null, "Error: " + ex.getMessage());
                    }
                } else {
                    JOptionPane.showMessageDialog(null, "Please fill in all fields.");
                }
            }
        });

        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    private byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private String hashPassword(String password, byte[] salt) throws Exception {
        java.security.MessageDigest md = java.security.MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return bytesToHex(hashedPassword);
    }

    private void storeUser(String username, String hashedPassword, byte[] salt) throws Exception {
        Connection conn = DriverManager.getConnection("jdbc:derby:memory:registrationDB;create=true");
        PreparedStatement stmt = conn.prepareStatement("CREATE TABLE IF NOT EXISTS users (username VARCHAR(255), password VARCHAR(255), salt VARCHAR(255))");
        stmt.executeUpdate();

        String saltHex = bytesToHex(salt);
        PreparedStatement insertStmt = conn.prepareStatement("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)");
        insertStmt.setString(1, username);
        insertStmt.setString(2, hashedPassword);
        insertStmt.setString(3, saltHex);
        insertStmt.executeUpdate();

        conn.close();
    }

    private String bytesToHex(byte[] bytes) {
        BigInteger bi = new BigInteger(1, bytes);
        return String.format("%0" + (bytes.length << 1) + "x", bi);
    }

    public static void main(String[] args) {
        new RegistrationForm();
    }
}