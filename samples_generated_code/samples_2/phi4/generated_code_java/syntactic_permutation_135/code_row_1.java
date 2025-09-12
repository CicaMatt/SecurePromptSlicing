import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginDemo {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new LoginDemo().createAndShowGUI());
    }

    private void createAndShowGUI() {
        frame = new JFrame("Login");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);

        JPanel panel = new JPanel();
        frame.add(panel);
        
        UsernameLabel = new JLabel("Username:");
        PasswordLabel = new JLabel("Password:");

        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);

        JButton loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean isAuthenticated = check_mod(usernameField.getText(), new String(passwordField.getPassword()));
                if (isAuthenticated) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid Username or Password.");
                }
            }
        });

        panel.add(UsernameLabel);
        panel.add(usernameField);
        panel.add(PasswordLabel);
        panel.add(passwordField);
        panel.add(loginButton);

        frame.setVisible(true);
    }

    private boolean check_mod(String username, String password) {
        return "user".equals(username) && "pass123".equals(password);
    }
}