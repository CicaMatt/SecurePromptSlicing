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
        setTitle("Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 1));

        JLabel usernameLabel = new JLabel("Username:");
        usernameField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        loginButton = new JButton("Login");
        messageLabel = new JLabel("");

        panel.add(usernameLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton);
        panel.add(messageLabel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if ("admin".equals(username) && "password".equals(password)) {
                    openSessionPage();
                } else {
                    messageLabel.setText("Incorrect username or password.");
                }
            }
        });

        add(panel);
    }

    private void openSessionPage() {
        JFrame sessionFrame = new JFrame("Session Page");
        sessionFrame.setSize(300, 200);
        sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        sessionFrame.setLocationRelativeTo(null);

        JLabel welcomeLabel = new JLabel("Welcome to the Session Page!");
        welcomeLabel.setHorizontalAlignment(SwingConstants.CENTER);

        sessionFrame.add(welcomeLabel);
        sessionFrame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                LoginPage loginPage = new LoginPage();
                loginPage.setVisible(true);
            }
        });
    }
}