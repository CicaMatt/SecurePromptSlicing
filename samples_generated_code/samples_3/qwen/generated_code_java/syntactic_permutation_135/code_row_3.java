import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApp {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Login");
        JPanel panel = new JPanel();
        JLabel userLabel = new JLabel("Username:");
        JTextField userText = new JTextField(20);
        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordText = new JPasswordField(20);
        JButton loginButton = new JButton("login");

        panel.add(userLabel);
        panel.add(userText);
        panel.add(passwordLabel);
        panel.add(passwordText);
        panel.add(loginButton);

        frame.setSize(350, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(panel);
        frame.setVisible(true);

        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = userText.getText();
                String password = new String(passwordText.getPassword());
                if (authenticate(username, password)) {
                    JOptionPane.showMessageDialog(frame, "Login Successful");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid Login Credentials");
                }
            }
        });
    }

    public static boolean authenticate(String username, String password) {
        return "admin".equals(username) && "password".equals(password);
    }
}