import java.sql.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApplication {

    private static final String DB_URL = "jdbc:sqlite:users.db";

    public static void main(String[] args) {
        createDatabase();
        SwingUtilities.invokeLater(LoginApplication::createAndShowGUI);
    }

    private static void createDatabase() {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            if (conn != null) {
                DatabaseMetaData meta = conn.getMetaData();
                System.out.println("The driver name is " + meta.getDriverName());
                Statement statement = conn.createStatement();

                String sqlCreate = "CREATE TABLE IF NOT EXISTS users (" +
                        "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                        "username TEXT NOT NULL UNIQUE," +
                        "password TEXT NOT NULL);";

                String sqlInsert = "INSERT INTO users (username, password) VALUES ('admin', '1234');";
                
                statement.execute(sqlCreate);
                try {
                    statement.execute(sqlInsert);
                } catch (SQLException e) {
                    System.out.println("User already exists.");
                }
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void createAndShowGUI() {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);

        JPanel panel = new JPanel();
        JTextField usernameField = new JTextField(15);
        JPasswordField passwordField = new JPasswordField(15);
        JButton loginButton = new JButton("Login");

        panel.add(new JLabel("Username:"));
        panel.add(usernameField);
        panel.add(Box.createHorizontalStrut(15)); 
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);

        loginButton.addActionListener(e -> {
            String username = usernameField.getText();
            char[] passwordArray = passwordField.getPassword();

            if (authenticateUser(username, new String(passwordArray))) {
                JOptionPane.showMessageDialog(frame, "Login Successful");
                // Redirect to dashboard
                frame.dispose();
                showDashboard();
            } else {
                JOptionPane.showMessageDialog(frame, "Invalid Credentials", "Error", JOptionPane.ERROR_MESSAGE);
            }
        });

        panel.add(loginButton);
        frame.getContentPane().add(panel);

        frame.setVisible(true);
    }

    private static boolean authenticateUser(String username, String password) {
        String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, password);

            ResultSet rs = pstmt.executeQuery();

            return rs.next();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            return false;
        }
    }

    private static void showDashboard() {
        JFrame frame = new JFrame("Dashboard");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 100);

        JLabel label = new JLabel("Welcome to the Dashboard!");
        JButton logoutButton = new JButton("Logout");

        logoutButton.addActionListener(e -> {
            frame.dispose();
            createAndShowGUI();
        });

        JPanel panel = new JPanel();
        panel.add(label);
        panel.add(logoutButton);

        frame.getContentPane().add(panel);
        frame.setVisible(true);
    }
}
