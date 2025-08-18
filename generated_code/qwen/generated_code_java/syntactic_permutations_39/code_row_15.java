import javax.swing.*;
import java.awt.event.*;

public class LoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginPage() {
        setTitle("Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(null);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setBounds(50, 20, 100, 20);
        add(usernameLabel);

        usernameField = new JTextField();
        usernameField.setBounds(160, 20, 100, 20);
        add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(50, 50, 100, 20);
        add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setBounds(160, 50, 100, 20);
        add(passwordField);

        loginButton = new JButton("Login");
        loginButton.setBounds(110, 90, 80, 20);
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());
                if ("user".equals(username) && "pass".equals(password)) {
                    openSessionPage();
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Invalid username or password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        add(loginButton);

        setVisible(true);
    }

    private void openSessionPage() {
        JFrame sessionPage = new JFrame("Session Page");
        sessionPage.setSize(300, 200);
        sessionPage.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        sessionPage.setLayout(null);

        JLabel welcomeLabel = new JLabel("Welcome to the Session Page!");
        welcomeLabel.setBounds(50, 80, 200, 20);
        sessionPage.add(welcomeLabel);

        sessionPage.setVisible(true);
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}