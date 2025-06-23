java
import javax.swing.*;
import java.awt.*;

public class LoginForm extends JFrame {
    private JLabel usernameLabel;
    private JTextField usernameField;
    private JLabel passwordLabel;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginForm() {
        super("Login");

        // create labels for the username and password fields
        usernameLabel = new JLabel("Username: ");
        passwordLabel = new JLabel("Password: ");

        // create text fields for the username and password
        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);

        // create login button
        loginButton = new JButton("Login");

        // add everything to the frame
        Container contentPane = getContentPane();
        contentPane.setLayout(new FlowLayout());
        contentPane.add(usernameLabel);
        contentPane.add(usernameField);
        contentPane.add(passwordLabel);
        contentPane.add(passwordField);
        contentPane.add(loginButton);
    }

    public static void main(String[] args) {
        LoginForm loginForm = new LoginForm();
        loginForm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        loginForm.pack();
        loginForm.setVisible(true);
    }
}