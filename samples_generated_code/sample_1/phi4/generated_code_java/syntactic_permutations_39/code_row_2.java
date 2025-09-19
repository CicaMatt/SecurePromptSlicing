import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {

    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JLabel statusLabel;

    public SimpleLoginPage() {
        setTitle("Simple Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        usernameField = new JTextField();
        passwordField = new JPasswordField();
        loginButton = new JButton("Login");
        statusLabel = new JLabel();

        add(new JLabel("Username:"));
        add(usernameField);
        add(new JLabel("Password:"));
        add(passwordField);
        add(loginButton);
        add(statusLabel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] password = passwordField.getPassword();

                if (isValidCredentials(username, new String(password))) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Login Successful! Redirecting to session page...",
                            "Success", JOptionPane.INFORMATION_MESSAGE);
                    // Redirect to session page or perform other actions
                } else {
                    statusLabel.setText("Incorrect username or password.");
                }
            }
        });

        setLocationRelativeTo(null); // Center the window
    }

    private boolean isValidCredentials(String username, String password) {
        // Hardcoded credentials for demonstration purposes
        return "user".equals(username) && "pass123".equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SimpleLoginPage loginPage = new SimpleLoginPage();
            loginPage.setVisible(true);
        });
    }
}