import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApplication {

    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password123";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        JPanel panel = new JPanel();
        JTextField usernameField = new JTextField(20);
        JPasswordField passwordField = new JPasswordField(20);
        JButton loginButton = new JButton("Login");

        panel.add(new JLabel("Username:"));
        panel.add(usernameField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(loginButton);

        frame.setContentPane(panel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (USERNAME.equals(username) && PASSWORD.equals(password)) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                    // Redirect to dashboard page logic here
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid Username or Password!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }
}