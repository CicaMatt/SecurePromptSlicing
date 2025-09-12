import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginChecker extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginChecker() {
        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);
        loginButton = new JButton("Login");

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = checkCredentials();
                JOptionPane.showMessageDialog(LoginChecker.this, "Login " + (result ? "successful" : "failed"));
            }
        });

        setLayout(null);
        usernameField.setBounds(50, 50, 200, 30);
        passwordField.setBounds(50, 100, 200, 30);
        loginButton.setBounds(50, 150, 200, 30);

        add(usernameField);
        add(passwordField);
        add(loginButton);

        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private boolean checkCredentials() {
        String username = usernameField.getText();
        char[] password = passwordField.getPassword();
        return "admin".equals(username) && "123456".equals(new String(password));
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginChecker loginChecker = new LoginChecker();
            loginChecker.setVisible(true);
        });
    }
}