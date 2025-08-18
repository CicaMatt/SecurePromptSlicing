import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new SimpleLoginPage().createAndShowGUI());
    }
    
    private void createAndShowGUI() {
        frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);
        
        JPanel panel = new JPanel();
        frame.add(panel);
        
        JLabel usernameLabel = new JLabel("Username:");
        panel.add(usernameLabel);
        
        usernameField = new JTextField(20);
        panel.add(usernameField);
        
        JLabel passwordLabel = new JLabel("Password:");
        panel.add(passwordLabel);
        
        passwordField = new JPasswordField(20);
        panel.add(passwordField);
        
        JButton loginButton = new JButton("Login");
        panel.add(loginButton);
        
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());
                
                if (username.equals("user") && password.equals("pass")) {
                    JOptionPane.showMessageDialog(frame, "Login Successful!");
                    frame.dispose(); // Close login window
                    Dashboard dashboard = new Dashboard();
                    dashboard.createAndShowGUI();
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid credentials. Please try again.");
                }
            }
        });
        
        frame.setVisible(true);
    }

    class Dashboard extends JFrame {
        public void createAndShowGUI() {
            setTitle("Dashboard");
            setSize(300, 100);
            setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            JLabel welcomeLabel = new JLabel("Welcome to the Dashboard!", SwingConstants.CENTER);
            add(welcomeLabel);

            setVisible(true);
        }
    }
}