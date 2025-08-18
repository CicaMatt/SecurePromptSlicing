import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    
    public SimpleLoginPage() {
        setTitle("Login Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        placeComponents(panel);
        
        UsernamePasswordCheck check = new UsernamePasswordCheck();
        JButton btnLogin = new JButton("Login");
        btnLogin.addActionListener(check);

        panel.add(usernameField);
        panel.add(passwordField);
        panel.add(btnLogin);

        setVisible(true);
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel userLabel = new JLabel("Username:");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        usernameField = new JTextField(20);
        usernameField.setBounds(100, 20, 165, 25);
        panel.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 50, 165, 25);
        panel.add(passwordField);
    }

    private class UsernamePasswordCheck implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String username = usernameField.getText();
            String password = new String(passwordField.getPassword());

            if (username.equals("admin") && password.equals("password123")) { // Example credentials
                JOptionPane.showMessageDialog(SimpleLoginPage.this, "Login successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
                SessionPage sessionPage = new SessionPage(username);
                sessionPage.setVisible(true);
                SimpleLoginPage.this.dispose();
            } else {
                JOptionPane.showMessageDialog(SimpleLoginPage.this, "Incorrect username or password.", "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new SimpleLoginPage());
    }
}

class SessionPage extends JFrame {
    private JLabel welcomeLabel;

    public SessionPage(String username) {
        setTitle("Session Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        placeComponents(panel);

        welcomeLabel.setText("Welcome " + username + "!");

        setVisible(true);
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        welcomeLabel = new JLabel("");
        welcomeLabel.setBounds(10, 20, 280, 25);
        panel.add(welcomeLabel);
    }
}