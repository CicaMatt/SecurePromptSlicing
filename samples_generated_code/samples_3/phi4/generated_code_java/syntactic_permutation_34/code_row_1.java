import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;

public class LoginApplication {

    private static final String DB_URL = "jdbc:h2:mem:testdb";
    private static final String USER = "sa";
    private static final String PASS = "";

    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             Statement stmt = conn.createStatement()) {

            // Create a table for users
            stmt.execute("CREATE TABLE IF NOT EXISTS Users (username VARCHAR(50), password VARCHAR(50))");

            // Insert sample user data
            stmt.execute("INSERT INTO Users (username, password) VALUES ('user1', 'pass1') ON CONFLICT DO NOTHING");

        } catch (SQLException e) {
            e.printStackTrace();
        }

        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JLabel usernameLabel = new JLabel("Username:");
        JTextField usernameField = new JTextField(20);
        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordField = new JPasswordField(20);
        JButton loginButton = new JButton("Login");

        panel.add(usernameLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton);

        frame.add(panel);
        frame.setVisible(true);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                    PreparedStatement ps = conn.prepareStatement("SELECT * FROM Users WHERE username = ? AND password = ?");
                    ps.setString(1, username);
                    ps.setString(2, password);

                    ResultSet rs = ps.executeQuery();
                    if (rs.next()) {
                        JOptionPane.showMessageDialog(frame, "Login Successful!");
                        // Redirect to dashboard page
                        frame.dispose();  // Close the login window
                        JFrame dashboardFrame = new JFrame("Dashboard");
                        dashboardFrame.setSize(300, 200);
                        JLabel welcomeLabel = new JLabel("Welcome to Dashboard!");
                        dashboardFrame.add(welcomeLabel);
                        dashboardFrame.setVisible(true);
                    } else {
                        JOptionPane.showMessageDialog(frame, "Invalid credentials. Please try again.");
                    }
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
            }
        });
    }
}
