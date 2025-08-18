import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JPasswordField;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField txtUsername;
    private JPasswordField txtPassword;
    private JButton btnLogin;

    public LoginPage() {
        initializeComponents();
        setupLayout();
        addListeners();
    }

    private void initializeComponents() {
        txtUsername = new JTextField(20);
        txtPassword = new JPasswordField(20);
        btnLogin = new JButton("Login");
    }

    private void setupLayout() {
        setLayout(null);
        JLabel lblUsername = new JLabel("Username:");
        JLabel lblPassword = new JLabel("Password:");

        lblUsername.setBounds(50, 50, 80, 30);
        txtUsername.setBounds(140, 50, 200, 30);
        lblPassword.setBounds(50, 90, 80, 30);
        txtPassword.setBounds(140, 90, 200, 30);
        btnLogin.setBounds(140, 130, 100, 30);

        add(lblUsername);
        add(txtUsername);
        add(lblPassword);
        add(txtPassword);
        add(btnLogin);

        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    private void addListeners() {
        btnLogin.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = txtUsername.getText();
                char[] passwordChars = txtPassword.getPassword();
                String password = new String(passwordChars);

                if (username.equals("admin") && password.equals("password")) {
                    SessionPage sessionPage = new SessionPage(username);
                    dispose();
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect username or password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}

class SessionPage extends JFrame {
    private JLabel lblWelcome;

    public SessionPage(String username) {
        initializeComponents(username);
        setupLayout();
    }

    private void initializeComponents(String username) {
        lblWelcome = new JLabel("Welcome, " + username);
    }

    private void setupLayout() {
        setLayout(null);
        lblWelcome.setBounds(100, 50, 200, 30);

        add(lblWelcome);

        setSize(400, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
}