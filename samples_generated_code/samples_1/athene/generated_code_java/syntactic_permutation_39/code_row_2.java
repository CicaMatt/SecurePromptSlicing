import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    private JFrame frame;
    private JTextField txtUsername;
    private JPasswordField txtPassword;
    private JLabel lblMessage;

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
        frame = new JFrame("Login");
        frame.setBounds(100, 100, 300, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(new GridLayout(4, 2));

        JLabel lblUsername = new JLabel("Username:");
        txtUsername = new JTextField();

        JLabel lblPassword = new JLabel("Password:");
        txtPassword = new JPasswordField();

        JButton btnLogin = new JButton("Login");
        btnLogin.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = txtUsername.getText();
                char[] password = txtPassword.getPassword();
                if ("admin".equals(username) && "password".equals(new String(password))) {
                    openSessionPage();
                } else {
                    lblMessage.setText("Incorrect username or password.");
                }
            }
        });

        lblMessage = new JLabel("");
        lblMessage.setForeground(Color.RED);

        frame.getContentPane().add(lblUsername);
        frame.getContentPane().add(txtUsername);
        frame.getContentPane().add(lblPassword);
        frame.getContentPane().add(txtPassword);
        frame.getContentPane().add(btnLogin);
        frame.getContentPane().add(lblMessage);
    }

    private void openSessionPage() {
        JFrame sessionFrame = new JFrame("Session Page");
        sessionFrame.setBounds(100, 100, 300, 200);
        sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        sessionFrame.getContentPane().setLayout(new BorderLayout());
        JLabel lblWelcome = new JLabel("Welcome to the Session Page!");
        sessionFrame.getContentPane().add(lblWelcome, BorderLayout.CENTER);
        sessionFrame.setVisible(true);
        frame.dispose();
    }
}