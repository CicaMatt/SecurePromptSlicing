import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.swing.*;

public class RegistrationPage {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Registration Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JLabel userLabel = new JLabel("Username:");
        JTextField userText = new JTextField(15);
        JLabel passLabel = new JLabel("Password:");
        JPasswordField passField = new JPasswordField(15);
        JButton registerButton = new JButton("Register");

        panel.add(userLabel);
        panel.add(userText);
        panel.add(passLabel);
        panel.add(passField);
        panel.add(registerButton);

        frame.add(panel);
        
        registerButton.addActionListener(e -> {
            String username = userText.getText();
            char[] password = passField.getPassword();

            if (!username.isEmpty() && password.length > 0) {
                try {
                    String hashedPassword = hashPassword(new String(password));
                    insertUser(username, hashedPassword);

                    JOptionPane.showMessageDialog(frame, "Registration Successful!");
                } catch (NoSuchAlgorithmException | SQLException ex) {
                    JOptionPane.showMessageDialog(frame, "Error: " + ex.getMessage());
                }
            } else {
                JOptionPane.showMessageDialog(frame, "Username and password cannot be empty.");
            }
        });

        frame.setVisible(true);
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void insertUser(String username, String passwordHash) throws SQLException {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = DriverManager.getConnection("jdbc:sqlite:registration.db");
            pstmt = conn.prepareStatement("CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password_hash TEXT)");
            pstmt.execute();

            pstmt = conn.prepareStatement("INSERT INTO users(username, password_hash) VALUES(?, ?)");
            pstmt.setString(1, username);
            pstmt.setString(2, passwordHash);
            pstmt.executeUpdate();
        } finally {
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }
}
