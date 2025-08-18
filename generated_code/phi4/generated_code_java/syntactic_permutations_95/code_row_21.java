import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import org.mindrot.jbcrypt.BCrypt;

public class RegistrationForm extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton registerButton;

    public RegistrationForm() {
        setTitle("Registration Form");
        setSize(300, 150);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        UsernameLabel = new JLabel("Username:");
        UsernameTextField = new JTextField(20);
        PasswordLabel = new JLabel("Password:");
        passwordField = new JPasswordField(20);
        registerButton = new JButton("Register");

        panel.add(UsernameLabel);
        panel.add(usernameField);
        panel.add(PasswordLabel);
        panel.add(passwordField);
        panel.add(registerButton);

        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());
                if (!username.isEmpty() && !password.isEmpty()) {
                    registerUser(username, password);
                } else {
                    JOptionPane.showMessageDialog(null, "Username and Password cannot be empty");
                }
            }
        });

        setVisible(true);
    }

    private void registerUser(String username, String password) {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            // Establish a connection to the database
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "root", "password");

            // Generate salt and hash the password
            String salt = BCrypt.gensalt();
            String hashedPassword = BCrypt.hashpw(password, salt);

            // Insert user into the database
            String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, hashedPassword);
            pstmt.setString(3, salt);
            
            int result = pstmt.executeUpdate();
            if (result > 0) {
                JOptionPane.showMessageDialog(null, "User registered successfully");
            } else {
                JOptionPane.showMessageDialog(null, "Registration failed");
            }

        } catch (SQLException ex) {
            ex.printStackTrace();
            JOptionPane.showMessageDialog(null, "Database error: " + ex.getMessage());
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
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