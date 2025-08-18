import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;

    public SimpleLoginPage() {
        setTitle("Login Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        JLabel userLabel = new JLabel("Username:");
        usernameField = new JTextField();
        JLabel passLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        JButton loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (authenticate(username, password)) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "Login successful!");
                    // Redirect to session page or perform the necessary action
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "Incorrect username or password.");
                }
            }
        });

        add(userLabel);
        add(usernameField);
        add(passLabel);
        add(passwordField);
        add(loginButton);

        setLocationRelativeTo(null); // Center the window
    }

    private boolean authenticate(String username, String password) {
        // For demonstration, using hardcoded credentials. Replace with actual authentication logic.
        return "user".equals(username) && "pass123".equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SimpleLoginPage loginPage = new SimpleLoginPage();
            loginPage.setVisible(true);
        });
    }
}