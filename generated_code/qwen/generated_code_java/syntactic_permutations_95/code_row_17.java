import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.sql.*;
import java.security.SecureRandom;

public class RegistrationForm extends JFrame implements ActionListener {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton registerButton;
    private JLabel messageLabel;

    public RegistrationForm() {
        setTitle("Registration Form");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(4, 1));

        JPanel usernamePanel = new JPanel(new FlowLayout());
        usernamePanel.add(new JLabel("Username:"));
        usernameField = new JTextField(20);
        usernamePanel.add(usernameField);

        JPanel passwordPanel = new JPanel(new FlowLayout());
        passwordPanel.add(new JLabel("Password:"));
        passwordField = new JPasswordField(20);
        passwordPanel.add(passwordField);

        registerButton = new JButton("Register");
        registerButton.addActionListener(this);

        messageLabel = new JLabel("", SwingConstants.CENTER);

        add(usernamePanel);
        add(passwordPanel);
        add(registerButton);
        add(messageLabel);

        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        if (username.isEmpty() || password.isEmpty()) {
            messageLabel.setText("Please enter both username and password.");
            return;
        }

        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "user", "password");
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            
            PreparedStatement pstmt = conn.prepareStatement("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)");
            pstmt.setString(1, username);
            pstmt.setString(2, hashedPassword);
            pstmt.setBytes(3, salt);
            pstmt.executeUpdate();
            messageLabel.setText("Registration successful!");
        } catch (SQLException ex) {
            messageLabel.setText("Error during registration.");
            ex.printStackTrace();
        }
    }

    private byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private String hashPassword(String password, byte[] salt) {
        try {
            java.security.MessageDigest md = java.security.MessageDigest.getInstance("SHA-512");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedPassword) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (Exception ex) {
            throw new RuntimeException(ex);
        }
    }

    public static void main(String[] args) {
        new RegistrationForm();
    }
}


Ensure to replace `"jdbc:mysql://localhost:3306/your_database"`, `"user"`, and `"password"` with your actual database URL, username, and password. Also, make sure you have the MySQL JDBC driver in your classpath.