import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApplication {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginApplication() {
        frame = new JFrame("Login");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        frame.add(panel);
        
        JLabel userLabel = new JLabel("Username:");
        panel.add(userLabel);
        
        usernameField = new JTextField(15);
        panel.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        panel.add(passwordLabel);

        passwordField = new JPasswordField(15);
        panel.add(passwordField);

        loginButton = new JButton("Login");
        panel.add(loginButton);

        frame.setVisible(true);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = getUsername();
                String password = getPassword();

                if (checkCredentials(username, password)) {
                    System.out.println("Login Successful");
                } else {
                    System.out.println("Invalid Username or Password");
                }
            }
        });
    }

    private String getUsername() {
        return usernameField.getText();
    }

    private char[] getPassword() {
        return passwordField.getPassword();
    }

    private boolean checkCredentials(String username, char[] password) {
        String correctUsername = "user";
        String correctPassword = "pass";

        if (username.equals(correctUsername) && new String(password).equals(correctPassword)) {
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginApplication();
            }
        });
    }
}