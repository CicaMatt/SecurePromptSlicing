import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JLabel messageLabel;

    public SimpleLoginPage() {
        setTitle("Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        
        JLabel userLabel = new JLabel("Username:");
        usernameField = new JTextField(15);
        
        JLabel passLabel = new JLabel("Password:");
        passwordField = new JPasswordField(15);
        
        loginButton = new JButton("Login");
        messageLabel = new JLabel("", SwingConstants.CENTER);

        panel.add(userLabel);
        panel.add(usernameField);
        panel.add(passLabel);
        panel.add(passwordField);
        panel.add(loginButton);
        panel.add(messageLabel);

        add(panel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (validateCredentials(username, password)) {
                    messageLabel.setText("Login successful!");
                    // Redirect to session page or next action
                } else {
                    messageLabel.setText("Incorrect username or password.");
                }
            }
        });
    }

    private boolean validateCredentials(String username, String password) {
        return "user".equals(username) && "pass123".equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SimpleLoginPage loginPage = new SimpleLoginPage();
            loginPage.setVisible(true);
        });
    }
}