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
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(4, 1));

        add(createPanel("Username:", usernameField));
        add(createPanel("Password:", passwordField));
        add(createPanel(loginButton));
        add(messageLabel);

        pack();
        setLocationRelativeTo(null);
    }

    private JPanel createPanel(String label, Component component) {
        JPanel panel = new JPanel(new BorderLayout());
        JLabel lbl = new JLabel(label, SwingConstants.RIGHT);
        panel.add(lbl, BorderLayout.WEST);
        panel.add(component, BorderLayout.CENTER);
        return panel;
    }

    private void addListeners() {
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] password = passwordField.getPassword();
                if (username.equals("admin") && new String(password).equals("password")) {
                    setVisible(false);
                    new SessionPage(username).setVisible(true);
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
    private JLabel welcomeLabel;

    public SessionPage(String username) {
        initializeComponents(username);
        setupLayout();
    }

    private void initializeComponents(String username) {
        welcomeLabel = new JLabel("Welcome, " + username + "!", SwingConstants.CENTER);
    }

    private void setupLayout() {
        setTitle("Session Page");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        add(welcomeLabel, BorderLayout.CENTER);

        pack();
        setLocationRelativeTo(null);
    }
}