import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginDemo extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginDemo() {
        setTitle("Login Demo");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        panel.add(new JLabel("Username:"));
        usernameField = new JTextField(15);
        panel.add(usernameField);

        panel.add(new JLabel("Password:"));
        passwordField = new JPasswordField(15);
        panel.add(passwordField);

        loginButton = new JButton("Login");
        panel.add(loginButton);

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

        setLocationRelativeTo(null);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());

        // Assuming the correct credentials are "user" and "pass"
        return "user".equals(username) && "pass".equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginDemo().setVisible(true);
            }
        });
    }
}