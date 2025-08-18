import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLogin {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Simple Login Page");
        frame.setSize(300, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        JLabel usernameLabel = new JLabel("Username:");
        JTextField usernameField = new JTextField(15);
        
        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordField = new JPasswordField(15);

        JButton loginButton = new JButton("Login");
        
        panel.add(usernameLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton);

        frame.setContentPane(panel);
        frame.setVisible(true);

        final String correctUsername = "user";
        final String correctPassword = "pass";

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordArray = passwordField.getPassword();

                if (correctUsername.equals(username) && new String(passwordArray).equals(correctPassword)) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                    // Redirect to another page or functionality here.
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid Username or Password", "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }
}