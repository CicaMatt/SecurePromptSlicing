import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;

public class LoginApplication {
    private static final String DB_URL = "jdbc:sqlite:users.db";

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Login Page");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(300, 200);

            JPanel panel = new JPanel();
            JLabel usernameLabel = new JLabel("Username:");
            JTextField usernameField = new JTextField(15);
            JLabel passwordLabel = new JLabel("Password:");
            JPasswordField passwordField = new JPasswordField(15);
            JButton loginButton = new JButton("Login");

            panel.add(usernameLabel);
            panel.add(usernameField);
            panel.add(passwordLabel);
            panel.add(passwordField);
            panel.add(loginButton);

            frame.setContentPane(panel);

            loginButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    String username = usernameField.getText();
                    String password = new String(passwordField.getPassword());

                    if (authenticateUser(username, password)) {
                        JOptionPane.showMessageDialog(frame, "Login Successful!");
                        // Redirect to Dashboard (Simulated here with a message)
                        frame.dispose(); // Close login window
                        JFrame dashboardFrame = new JFrame("Dashboard");
                        dashboardFrame.setSize(300, 200);
                        dashboardFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                        JLabel welcomeLabel = new JLabel("Welcome to the Dashboard!");
                        dashboardFrame.add(welcomeLabel);
                        dashboardFrame.setVisible(true);
                    } else {
                        JOptionPane.showMessageDialog(frame, "Invalid Username or Password. Please try again.");
                    }
                }
            });

            frame.setLocationRelativeTo(null); // Center on screen
            frame.setVisible(true);

            initializeDatabase();
        });
    }

    private static void initializeDatabase() {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            if (conn != null) {
                Statement stmt = conn.createStatement();
                String sql = "CREATE TABLE IF NOT EXISTS users (" +
                        "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                        "username TEXT NOT NULL UNIQUE," +
                        "password TEXT NOT NULL" +
                        ");";
                stmt.execute(sql);

                // Insert a test user (for demonstration purposes)
                try (PreparedStatement pstmt = conn.prepareStatement("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?);")) {
                    pstmt.setString(1, "testuser");
                    pstmt.setString(2, "password123");
                    pstmt.executeUpdate();
                }
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static boolean authenticateUser(String username, String password) {
        String sql = "SELECT id FROM users WHERE username = ? AND password = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, password);

            ResultSet rs = pstmt.executeQuery();
            return rs.next(); // Returns true if a row is found
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            return false;
        }
    }
}