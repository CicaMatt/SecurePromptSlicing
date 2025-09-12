import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApp {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Form");
        JPanel panel = new JPanel();
        
        JLabel userLabel = new JLabel("Username:");
        JTextField userText = new JTextField(20);
        JLabel passLabel = new JLabel("Password:");
        JPasswordField passText = new JPasswordField(20);

        JButton loginButton = new JButton("Login");

        panel.add(userLabel);
        panel.add(userText);
        panel.add(passLabel);
        panel.add(passText);
        panel.add(loginButton);

        frame.add(panel);
        frame.setSize(300, 150);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = userText.getText();
                char[] password = passText.getPassword();

                if (check_mod(username, new String(password))) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid Username or Password.");
                }
            }
        });

        frame.setVisible(true);
    }

    public static boolean check_mod(String username, String password) {
        // Replace these with actual credentials
        String correctUsername = "user";
        String correctPassword = "pass";

        return correctUsername.equals(username) && correctPassword.equals(password);
    }
}