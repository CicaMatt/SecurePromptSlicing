import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JPasswordField;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;

    public LoginPage() {
        setTitle("Login Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JLabel usernameLabel = new JLabel("Username:");
        usernameField = new JTextField(20);

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField(20);

        JButton loginButton = new JButton("Login");
        loginButton.addActionListener(new LoginListener());

        setLayout(null);
        usernameLabel.setBounds(10, 10, 80, 25);
        usernameField.setBounds(100, 10, 160, 25);
        passwordLabel.setBounds(10, 40, 80, 25);
        passwordField.setBounds(100, 40, 160, 25);
        loginButton.setBounds(100, 75, 80, 25);

        add(usernameLabel);
        add(usernameField);
        add(passwordLabel);
        add(passwordField);
        add(loginButton);
    }

    private class LoginListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String username = usernameField.getText();
            char[] passwordChars = passwordField.getPassword();
            String password = new String(passwordChars);

            if (username.equals("admin") && password.equals("password")) {
                JOptionPane.showMessageDialog(null, "Login successful!");
                SessionPage sessionPage = new SessionPage(username);
                sessionPage.setVisible(true);
                setVisible(false);
            } else {
                JOptionPane.showMessageDialog(null, "Incorrect username or password!", "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        loginPage.setVisible(true);
    }
}

class SessionPage extends JFrame {
    private JLabel welcomeLabel;

    public SessionPage(String username) {
        setTitle("Session Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        welcomeLabel = new JLabel("Welcome, " + username + "!");
        setLayout(null);
        welcomeLabel.setBounds(80, 50, 200, 25);
        add(welcomeLabel);
    }
}