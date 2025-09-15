import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm extends Frame implements ActionListener {
    private TextField usernameField, passwordField;
    private Button registerButton;
    private Label usernameLabel, passwordLabel;

    public RegistrationForm() {
        setLayout(new GridLayout(4, 2));
        setTitle("Registration Form");
        setSize(300, 150);
        setVisible(true);

        usernameLabel = new Label("Username: ");
        add(usernameLabel);
        usernameField = new TextField();
        add(usernameField);

        passwordLabel = new Label("Password: ");
        add(passwordLabel);
        passwordField = new TextField();
        passwordField.setEchoChar('*');
        add(passwordField);

        registerButton = new Button("Register");
        add(registerButton);
        registerButton.addActionListener(this);

        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent windowEvent) {
                System.exit(0);
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == registerButton) {
            String username = usernameField.getText();
            String password = passwordField.getText();

            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);

            try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "user", "password")) {
                String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
                PreparedStatement pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, username);
                pstmt.setString(2, hashedPassword);
                pstmt.setBytes(3, salt);

                int affectedRows = pstmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("Registration successful.");
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
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
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        new RegistrationForm();
    }
}
