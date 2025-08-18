import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    private static final String VALID_USERNAME = "admin";
    private static final String VALID_PASSWORD = "password";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);
        frame.setLayout(null);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setBounds(50, 10, 80, 25);
        frame.add(usernameLabel);

        JTextField userText = new JTextField();
        userText.setBounds(140, 10, 120, 25);
        frame.add(userText);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(50, 50, 80, 25);
        frame.add(passwordLabel);

        JPasswordField passwordText = new JPasswordField();
        passwordText.setBounds(140, 50, 120, 25);
        frame.add(passwordText);

        JButton loginButton = new JButton("Login");
        loginButton.setBounds(140, 90, 80, 25);
        frame.add(loginButton);

        JLabel messageLabel = new JLabel("");
        messageLabel.setBounds(70, 130, 200, 25);
        frame.add(messageLabel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = userText.getText();
                String password = new String(passwordText.getPassword());

                if (username.equals(VALID_USERNAME) && password.equals(VALID_PASSWORD)) {
                    messageLabel.setText("Login Successful!");
                } else {
                    messageLabel.setText("Invalid Username or Password.");
                }
            }
        });

        frame.setVisible(true);
    }
}