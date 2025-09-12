import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {

    private static final String USERNAME = "user";
    private static final String PASSWORD = "pass";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);

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

        frame.add(panel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (USERNAME.equals(username) && PASSWORD.equals(password)) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                    SessionPage sessionPage = new SessionPage();
                    sessionPage.setVisible(true);
                } else {
                    JOptionPane.showMessageDialog(frame, "Incorrect Username or Password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        frame.setLocationRelativeTo(null); // Center the window
        frame.setVisible(true);
    }

    static class SessionPage extends JFrame {

        public SessionPage() {
            setTitle("Session Page");
            setSize(300, 150);
            setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

            JLabel welcomeLabel = new JLabel("Welcome to your session!");
            add(welcomeLabel);

            setLocationRelativeTo(null); // Center the window
        }
    }
}