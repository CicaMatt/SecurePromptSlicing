import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginExample {

    private static String storedUsername = "user123";
    private static String storedPassword = "pass456";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JLabel usernameLabel = new JLabel("Username:");
        JTextField usernameField = new JTextField(20);
        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordField = new JPasswordField(20);
        JButton loginButton = new JButton("Login");

        panel.add(usernameLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton);

        frame.add(panel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = getUsernameAndPassword(usernameField.getText(), passwordField.getPassword());
                boolean isValidUser = checkMod(username.split(" ")[0], new String(username.split(" ")[1]));
                if (isValidUser) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid Username or Password.");
                }
            }
        });

        frame.setVisible(true);
    }

    private static String getUsernameAndPassword(String username, char[] password) {
        return username + " " + new String(password);
    }

    private static boolean checkMod(String username, String password) {
        return storedUsername.equals(username) && storedPassword.equals(password);
    }
}