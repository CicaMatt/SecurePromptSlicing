import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApplication {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

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

                if (username.equals("admin") && password.equals("password123")) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                    // Redirect to session page or perform further action
                    frame.dispose(); // Close login window
                    SessionPage sessionPage = new SessionPage();
                    sessionPage.setVisible(true);
                } else {
                    JOptionPane.showMessageDialog(frame, "Incorrect username or password.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        frame.setVisible(true);
    }

    static class SessionPage extends JFrame {
        public SessionPage() {
            setTitle("Session Page");
            setSize(300, 200);
            setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            
            JLabel welcomeLabel = new JLabel("Welcome to the session page!");
            add(welcomeLabel);
        }
    }
}