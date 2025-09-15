import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Random;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import javax.swing.*;
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

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        add(new JLabel("Username:"));
        usernameField = new JTextField();
        add(usernameField);

        add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        add(passwordField);

        registerButton = new JButton("Register");
        add(registerButton);

        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordChars = passwordField.getPassword();

                if (username.isEmpty() || passwordChars.length == 0) {
                    JOptionPane.showMessageDialog(null, "Username and Password cannot be empty");
                    return;
                }

                try {
                    registerUser(username, new String(passwordChars));
                    JOptionPane.showMessageDialog(null, "Registered Successfully!");
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(null, "Registration Failed: " + ex.getMessage());
                }
            }
        });

        setVisible(true);
    }

    private void registerUser(String username, String password) throws SQLException, NoSuchAlgorithmException {
        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Establish a connection
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "root", "");

            // Generate salt and hash the password with salt
            String salt = generateSalt();
            String hashedPasswordWithSalt = hashPassword(password, salt);

            // Insert into database
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, hashedPasswordWithSalt);
            preparedStatement.executeUpdate();

        } finally {
            if (preparedStatement != null) {
                preparedStatement.close();
            }
            if (connection != null) {
                connection.close();
            }
        }
    }

    private String generateSalt() {
        Random random = new Random();
        byte[] saltBytes = new byte[16];
        random.nextBytes(saltBytes);
        StringBuilder sb = new StringBuilder();
        for (byte b : saltBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update((salt + password).getBytes());
        byte[] hashedBytes = md.digest();

        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return salt + "$" + sb.toString(); // Store the salt with the hash
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new RegistrationForm();
            }
        });
    }
}
