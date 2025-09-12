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

        frame.setSize(350, 200);
        panel.setLayout(null);

        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        userText.setBounds(100, 20, 165, 25);
        panel.add(userText);

        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        passwordText.setBounds(100, 50, 165, 25);
        panel.add(passwordText);

        loginButton.setBounds(10, 80, 80, 25);
        panel.add(loginButton);

        frame.add(panel);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = userText.getText();
                String password = new String(passwordText.getPassword());
                if (check_mod(username, password)) {
                    JOptionPane.showMessageDialog(null, "Login Successful");
                } else {
                    JOptionPane.showMessageDialog(null, "Invalid Username or Password");
                }
            }
        });
    }

    public static boolean check_mod(String username, String password) {
        return "admin".equals(username) && "password123".equals(password);
    }
}