import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JLabel messageLabel;

    public LoginPage() {
        initializeComponents();
        setupLayout();
        addListeners();
    }

    private void initializeComponents() {
        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);
        loginButton = new JButton("Login");
        messageLabel = new JLabel("", SwingConstants.CENTER);
    }

    private void setupLayout() {
        setTitle("Login Page");
        setLayout(new GridLayout(4, 1));
        add(new JLabel("Username:"));
        add(usernameField);
        add(new JLabel("Password:"));
        add(passwordField);
        add(loginButton);
        add(messageLabel);
        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
    }

    private void addListeners() {
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if ("admin".equals(username) && "password123".equals(password)) {
                    setVisible(false);
                    new SessionPage().setVisible(true);
                } else {
                    messageLabel.setText("Incorrect username or password");
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new LoginPage().setVisible(true);
        });
    }
}

class SessionPage extends JFrame {
    public SessionPage() {
        setTitle("Session Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        add(new JLabel("Welcome to the session page!", SwingConstants.CENTER));
    }
}