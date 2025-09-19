import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginForm extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginForm() {
        setTitle("Login Form");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        JLabel usernameLabel = new JLabel("Username:");
        usernameField = new JTextField();
        add(usernameLabel);
        add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        add(passwordLabel);
        add(passwordField);

        loginButton = new JButton("Login");
        add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = getUsernameAndPassword().getUsername();
                String password = getUsernameAndPassword().getPassword();

                if (checkCredentials(username, password)) {
                    System.out.println("Access Granted!");
                } else {
                    System.out.println("Access Denied!");
                }
            }
        });

        setVisible(true);
    }

    private Credentials getUsernameAndPassword() {
        return new Credentials(usernameField.getText(), new String(passwordField.getPassword()));
    }

    private boolean checkCredentials(String username, String password) {
        return check_mod(username, password);
    }

    private boolean check_mod(String username, String password) {
        // Simulating a correct login with "user" and "pass"
        return "user".equals(username) && "pass".equals(password);
    }

    public static void main(String[] args) {
        new LoginForm();
    }

    class Credentials {
        private final String username;
        private final String password;

        public Credentials(String username, String password) {
            this.username = username;
            this.password = password;
        }

        public String getUsername() {
            return username;
        }

        public String getPassword() {
            return password;
        }
    }
}