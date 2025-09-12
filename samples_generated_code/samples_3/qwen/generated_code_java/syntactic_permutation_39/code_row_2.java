import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JLabel messageLabel;

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                LoginPage window = new LoginPage();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    public LoginPage() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblUsername = new JLabel("Username:");
        lblUsername.setBounds(62, 74, 86, 14);
        frame.getContentPane().add(lblUsername);

        JLabel lblPassword = new JLabel("Password:");
        lblPassword.setBounds(62, 105, 86, 14);
        frame.getContentPane().add(lblPassword);

        usernameField = new JTextField();
        usernameField.setBounds(158, 71, 130, 20);
        frame.getContentPane().add(usernameField);
        usernameField.setColumns(10);

        passwordField = new JPasswordField();
        passwordField.setBounds(158, 102, 130, 20);
        frame.getContentPane().add(passwordField);

        JButton btnLogin = new JButton("Login");
        btnLogin.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if ("admin".equals(username) && "password".equals(password)) {
                    openSessionPage();
                } else {
                    messageLabel.setText("Invalid username or password");
                }
            }
        });
        btnLogin.setBounds(158, 143, 89, 23);
        frame.getContentPane().add(btnLogin);

        messageLabel = new JLabel("");
        messageLabel.setForeground(Color.RED);
        messageLabel.setBounds(62, 177, 300, 14);
        frame.getContentPane().add(messageLabel);
    }

    private void openSessionPage() {
        JFrame sessionFrame = new JFrame();
        sessionFrame.setTitle("Session Page");
        sessionFrame.setSize(300, 200);
        sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JLabel lblWelcome = new JLabel("Welcome to the Session Page!");
        lblWelcome.setHorizontalAlignment(SwingConstants.CENTER);
        lblWelcome.setBounds(20, 75, 260, 14);
        sessionFrame.getContentPane().setLayout(null);
        sessionFrame.getContentPane().add(lblWelcome);
        sessionFrame.setVisible(true);
    }
}