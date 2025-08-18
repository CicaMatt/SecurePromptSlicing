import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    private JFrame frame;
    private JTextField txtUsername;
    private JPasswordField txtPassword;
    
    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                LoginPage window = new LoginPage();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    public LoginPage() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame("Login Page");
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblUsername = new JLabel("Username:");
        lblUsername.setBounds(79, 82, 67, 15);
        frame.getContentPane().add(lblUsername);

        txtUsername = new JTextField();
        txtUsername.setBounds(154, 79, 130, 20);
        frame.getContentPane().add(txtUsername);
        txtUsername.setColumns(10);

        JLabel lblPassword = new JLabel("Password:");
        lblPassword.setBounds(79, 126, 67, 15);
        frame.getContentPane().add(lblPassword);

        txtPassword = new JPasswordField();
        txtPassword.setBounds(154, 123, 130, 20);
        frame.getContentPane().add(txtPassword);

        JButton btnLogin = new JButton("Login");
        btnLogin.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = txtUsername.getText();
                char[] passwordChars = txtPassword.getPassword();
                String password = new String(passwordChars);

                if ("admin".equals(username) && "12345".equals(password)) {
                    JOptionPane.showMessageDialog(frame, "Login successful!");
                    // Redirect logic here
                } else {
                    JOptionPane.showMessageDialog(frame, "Incorrect username or password.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        btnLogin.setBounds(154, 167, 89, 23);
        frame.getContentPane().add(btnLogin);
    }
}