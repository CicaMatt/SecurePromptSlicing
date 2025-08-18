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
        initializeUI();
    }

    private void initializeUI() {
        setTitle("Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        usernameField = new JTextField(15);
        passwordField = new JPasswordField(15);
        loginButton = new JButton("Login");
        messageLabel = new JLabel("");

        JPanel panel = new JPanel(new GridLayout(4, 1));
        panel.add(createLabel("Username:"));
        panel.add(usernameField);
        panel.add(createLabel("Password:"));
        panel.add(passwordField);
        panel.add(loginButton);
        panel.add(messageLabel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] password = passwordField.getPassword();
                if ("admin".equals(username) && "password".equals(new String(password))) {
                    messageLabel.setText("");
                    openSessionPage();
                } else {
                    messageLabel.setForeground(Color.RED);
                    messageLabel.setText("Incorrect username or password");
                }
            }
        });

        add(panel);
    }

    private JLabel createLabel(String text) {
        JLabel label = new JLabel(text, SwingConstants.TRAILING);
        return label;
    }

    private void openSessionPage() {
        dispose();
        JFrame sessionFrame = new JFrame("Session Page");
        sessionFrame.setSize(300, 200);
        sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        sessionFrame.setLocationRelativeTo(null);
        JLabel welcomeLabel = new JLabel("Welcome to the Session Page!");
        sessionFrame.add(welcomeLabel, BorderLayout.CENTER);
        sessionFrame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}