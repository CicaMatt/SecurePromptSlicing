import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.swing.*;

public class LoginPage {

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Login");
            JLabel usernameLabel = new JLabel("Username:");
            JTextField usernameField = new JTextField(20);
            JLabel passwordLabel = new JLabel("Password:");
            JPasswordField passwordField = new JPasswordField(20);
            JButton loginButton = new JButton("Login");

            loginButton.addActionListener(e -> {
                String username = usernameField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if (login(username, password)) {
                    frame.dispose();
                    showHomePage();
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid username or password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            });

            JPanel panel = new JPanel();
            panel.add(usernameLabel);
            panel.add(usernameField);
            panel.add(passwordLabel);
            panel.add(passwordField);
            panel.add(loginButton);

            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.getContentPane().add(panel);
            frame.pack();
            frame.setVisible(true);
        });
    }

    private static boolean login(String username, String password) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_db_user";
        String dbPassword = "your_db_password";

        try (Connection conn = DriverManager.getConnection(url, user, dbPassword);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ?")) {
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                String storedPassword = rs.getString("password");
                return password.equals(storedPassword);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private static void showHomePage() {
        JFrame homeFrame = new JFrame("Home Page");
        JLabel welcomeLabel = new JLabel("Welcome to the Home Page!");

        JPanel panel = new JPanel();
        panel.add(welcomeLabel);

        homeFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        homeFrame.getContentPane().add(panel);
        homeFrame.pack();
        homeFrame.setVisible(true);
    }
}