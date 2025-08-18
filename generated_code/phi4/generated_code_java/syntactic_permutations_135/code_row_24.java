import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginDemo extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginDemo() {
        setTitle("Login Demo");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 150);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        add(new JLabel("Username:"));
        usernameField = new JTextField();
        add(usernameField);

        add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        add(passwordField);

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (check_mod()) {
                    JOptionPane.showMessageDialog(LoginDemo.this, "Login Successful!");
                } else {
                    JOptionPane.showMessageDialog(LoginDemo.this, "Invalid Username or Password.");
                }
            }
        });
        add(loginButton);

        setVisible(true);
    }

    private boolean check_mod() {
        String correctUsername = "user";
        String correctPassword = "password";

        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());

        return correctUsername.equals(username) && correctPassword.equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(LoginDemo::new);
    }
}