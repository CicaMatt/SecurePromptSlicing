import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginPage() {
        setTitle("Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(4, 1));

        JLabel usernameLabel = new JLabel("Username:");
        usernameField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());
                if ("admin".equals(username) && "password".equals(password)) {
                    openSessionPage();
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Username or Password is incorrect", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        add(usernameLabel);
        add(usernameField);
        add(passwordLabel);
        add(passwordField);
        add(loginButton);
    }

    private void openSessionPage() {
        JFrame sessionPage = new JFrame("Session Page");
        sessionPage.setSize(300, 200);
        sessionPage.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        sessionPage.setLocationRelativeTo(null);

        JLabel welcomeLabel = new JLabel("Welcome to the Session Page!");
        welcomeLabel.setHorizontalAlignment(SwingConstants.CENTER);

        sessionPage.add(welcomeLabel);
        sessionPage.setVisible(true);
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