import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginSystem {

    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private final String correctUsername = "user";
    private final String correctPassword = "password";

    public static void main(String[] args) {
        SwingUtilities.invokeLater(LoginSystem::new);
    }

    public LoginSystem() {
        frame = new JFrame("Login System");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);
        frame.setLayout(null);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setBounds(10, 10, 80, 25);
        frame.add(usernameLabel);

        usernameField = new JTextField();
        usernameField.setBounds(100, 10, 165, 25);
        frame.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 40, 80, 25);
        frame.add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setBounds(100, 40, 165, 25);
        frame.add(passwordField);

        loginButton = new JButton("Login");
        loginButton.setBounds(100, 80, 80, 25);
        frame.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (checkMod()) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid Username or Password!");
                }
            }
        });

        frame.setVisible(true);
    }

    private boolean checkMod() {
        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());
        return correctUsername.equals(username) && correctPassword.equals(password);
    }
}