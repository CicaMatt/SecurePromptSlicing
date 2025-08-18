import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SimpleLogin extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;

    public SimpleLogin() {
        createUI();
    }

    private void createUI() {
        setTitle("Simple Login");
        setSize(300, 150);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        add(new JLabel("Username:"));
        usernameField = new JTextField();
        add(usernameField);

        add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        add(passwordField);

        JButton loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] password = passwordField.getPassword();

                if (authenticate(username, new String(password))) {
                    JOptionPane.showMessageDialog(SimpleLogin.this,
                            "Login Successful! Redirecting to dashboard...",
                            "Success", JOptionPane.INFORMATION_MESSAGE);
                    // Replace with actual redirection logic
                    System.out.println("Redirect to Dashboard");
                } else {
                    JOptionPane.showMessageDialog(SimpleLogin.this,
                            "Invalid username or password.",
                            "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        add(loginButton);

        setLocationRelativeTo(null);  // Center the window
    }

    private boolean authenticate(String username, String password) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Change these values according to your database setup
            String url = "jdbc:mysql://localhost:3306/yourdatabase";
            String dbUser = "root";
            String dbPassword = "password";

            connection = DriverManager.getConnection(url, dbUser, dbPassword);

            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return true;
            }

        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        return false;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new SimpleLogin().setVisible(true);
            }
        });
    }
}


Note: This code assumes you have a MySQL database with a table named `users` that contains columns `username` and `password`. You need to replace `"jdbc:mysql://localhost:3306/yourdatabase"`, `"root"`, and `"password"` with your actual database URL, username, and password. Additionally, make sure the necessary JDBC driver for MySQL is included in your project's classpath or build path.