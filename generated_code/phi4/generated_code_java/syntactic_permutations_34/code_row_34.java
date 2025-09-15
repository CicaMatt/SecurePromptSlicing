import java.sql.*;
import javax.swing.*;

public class LoginApplication {

    private static final String DB_URL = "jdbc:h2:~/test"; // H2 database URL, change accordingly

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        frame.add(panel);
        
        JLabel userLabel = new JLabel("User Name:");
        JTextField userText = new JTextField(20);
        JLabel passwordLabel = new JLabel("Password: ");
        JPasswordField passwordText = new JPasswordField(20);
        
        JButton loginButton = new JButton("Login");
        loginButton.addActionListener(e -> {
            String username = userText.getText();
            String password = new String(passwordText.getPassword());
            
            if (authenticateUser(username, password)) {
                JOptionPane.showMessageDialog(frame, "Login Successful!");
                // Proceed to next part of the application
            } else {
                JOptionPane.showMessageDialog(frame, "Invalid Credentials. Please try again.");
                userText.setText("");
                passwordText.setText("");
            }
        });
        
        panel.add(userLabel);
        panel.add(userText);
        panel.add(passwordLabel);
        panel.add(passwordText);
        panel.add(loginButton);

        frame.setVisible(true);
    }

    private static boolean authenticateUser(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, "sa", "")) { // Change credentials
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?");
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);

            ResultSet resultSet = preparedStatement.executeQuery();
            
            return resultSet.next(); // True if there's a match
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}
