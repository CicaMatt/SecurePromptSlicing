import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.swing.JOptionPane;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        java.awt.EventQueue.invokeLater(() -> new LoginFrame().setVisible(true));
    }

    public static boolean login(String username, String password) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT * FROM users WHERE username = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                String storedPassword = rs.getString("password");
                if (storedPassword.equals(password)) {
                    // Redirect to home page
                    redirectToHomePage();
                    return true;
                } else {
                    JOptionPane.showMessageDialog(null, "Incorrect password.");
                    return false;
                }
            } else {
                JOptionPane.showMessageDialog(null, "Username does not exist.");
                return false;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    private static void redirectToHomePage() {
        // Logic to redirect to home page
        System.out.println("Redirecting to Home Page...");
        // For example: new HomePage().setVisible(true);
    }
}

class LoginFrame extends javax.swing.JFrame {

    private javax.swing.JButton loginButton;
    private javax.swing.JLabel usernameLabel;
    private javax.swing.JLabel passwordLabel;
    private javax.swing.JTextField usernameField;
    private javax.swing.JPasswordField passwordField;

    public LoginFrame() {
        initComponents();
    }

    private void initComponents() {
        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Login");

        usernameLabel = new javax.swing.JLabel("Username:");
        passwordLabel = new javax.swing.JLabel("Password:");
        usernameField = new javax.swing.JTextField(20);
        passwordField = new javax.swing.JPasswordField(20);
        loginButton = new javax.swing.JButton("Login");

        loginButton.addActionListener(evt -> {
            String username = usernameField.getText();
            String password = new String(passwordField.getPassword());
            LoginSystem.login(username, password);
        });

        java.awt.FlowLayout flowLayout = new java.awt.FlowLayout(java.awt.FlowLayout.CENTER, 5, 5);
        getContentPane().setLayout(flowLayout);

        getContentPane().add(usernameLabel);
        getContentPane().add(usernameField);
        getContentPane().add(passwordLabel);
        getContentPane().add(passwordField);
        getContentPane().add(loginButton);

        pack();
    }
}