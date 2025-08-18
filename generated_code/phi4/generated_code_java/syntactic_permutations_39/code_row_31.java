import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLogin {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel userLabel = new JLabel("User Name :");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        JTextField userNameText = new JTextField(20);
        userNameText.setBounds(100, 20, 165, 25);
        panel.add(userNameText);

        JLabel passwordLabel = new JLabel("Password :");
        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        JPasswordField passwordText = new JPasswordField();
        passwordText.setBounds(100, 50, 165, 25);
        panel.add(passwordText);

        JButton loginButton = new JButton("Login");
        loginButton.setBounds(10, 80, 80, 25);
        panel.add(loginButton);

        final JLabel messageLabel = new JLabel("");
        messageLabel.setBounds(10, 110, 250, 25);
        panel.add(messageLabel);

        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String userName = userNameText.getText();
                char[] passwordArray = passwordText.getPassword();
                String password = new String(passwordArray);

                if (userName.equals("admin") && password.equals("password")) {
                    messageLabel.setText("Login Successful!");
                    // Redirect to session page logic can be added here
                } else {
                    messageLabel.setText("Invalid username or password.");
                }
            }
        });
    }
}