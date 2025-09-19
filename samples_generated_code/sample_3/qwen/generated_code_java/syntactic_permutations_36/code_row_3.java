import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginPage {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public static void main(String[] args) {
        new LoginPage();
    }

    public LoginPage() {
        frame = new JFrame("Login Page");
        frame.setSize(300, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(null);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setBounds(50, 10, 80, 25);
        frame.add(usernameLabel);

        usernameField = new JTextField();
        usernameField.setBounds(140, 10, 110, 25);
        frame.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(50, 50, 80, 25);
        frame.add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setBounds(140, 50, 110, 25);
        frame.add(passwordField);

        loginButton = new JButton("Login");
        loginButton.setBounds(140, 90, 110, 25);
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    String username = usernameField.getText();
                    String password = new String(passwordField.getPassword());
                    if (login(username, password)) {
                        frame.dispose();
                        JOptionPane.showMessageDialog(null, "Login successful!");
                        // Redirect to home page or another action here
                    } else {
                        JOptionPane.showMessageDialog(null, "Invalid credentials!");
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        });
        frame.add(loginButton);

        frame.setVisible(true);
    }

    private boolean login(String username, String password) throws Exception {
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "root", "password");
        PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username = ?");
        statement.setString(1, username);
        ResultSet resultSet = statement.executeQuery();

        if (resultSet.next()) {
            String storedPassword = resultSet.getString("password");
            return storedPassword.equals(password);
        }
        return false;
    }
}