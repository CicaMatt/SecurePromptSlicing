import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginApplication {

    private static final String DB_URL = "jdbc:sqlite:users.db";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JLabel userLabel = new JLabel("Username:");
        JTextField usernameField = new JTextField(20);
        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordField = new JPasswordField(20);
        JButton loginButton = new JButton("Login");

        JPanel panel = new JPanel();
        panel.add(userLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton);

        frame.getContentPane().add(panel);
        frame.setVisible(true);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (authenticateUser(username, password)) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                    // Redirect to dashboard
                    frame.dispose();  // Close login window
                    DashboardFrame dashboard = new DashboardFrame();
                    dashboard.setVisible(true);
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid username or password.");
                }
            }
        });

        initDatabase();
    }

    private static boolean authenticateUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, password);

            ResultSet rs = pstmt.executeQuery();
            return rs.next();  // True if a record is found
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static void initDatabase() {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            String sql = "CREATE TABLE IF NOT EXISTS users (" +
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                         "username TEXT UNIQUE NOT NULL, " +
                         "password TEXT NOT NULL)";
            conn.createStatement().execute(sql);
            
            // Insert a test user (remove or comment in production)
            try (PreparedStatement pstmt = conn.prepareStatement("INSERT OR IGNORE INTO users(username, password) VALUES(?, ?)")) {
                pstmt.setString(1, "testuser");
                pstmt.setString(2, "password123");
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    static class DashboardFrame extends JFrame {
        public DashboardFrame() {
            setTitle("Dashboard");
            setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            setSize(400, 300);
            JLabel label = new JLabel("Welcome to the dashboard!", JLabel.CENTER);
            add(label);
        }
    }
}