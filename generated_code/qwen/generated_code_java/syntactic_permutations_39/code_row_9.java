import javax.swing.*;
import java.awt.event.*;

public class LoginPage {
    private JFrame frame;
    private JTextField textField;
    private JPasswordField passwordField;

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
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblUsername = new JLabel("Username:");
        lblUsername.setBounds(62, 78, 79, 14);
        frame.getContentPane().add(lblUsername);

        textField = new JTextField();
        textField.setBounds(153, 75, 160, 20);
        frame.getContentPane().add(textField);
        textField.setColumns(10);

        JLabel lblPassword = new JLabel("Password:");
        lblPassword.setBounds(62, 124, 89, 14);
        frame.getContentPane().add(lblPassword);

        passwordField = new JPasswordField();
        passwordField.setBounds(153, 121, 160, 20);
        frame.getContentPane().add(passwordField);

        JButton btnLogin = new JButton("Login");
        btnLogin.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = textField.getText();
                String password = new String(passwordField.getPassword());

                if ("admin".equals(username) && "password".equals(password)) {
                    showSessionPage();
                } else {
                    JOptionPane.showMessageDialog(frame, "Username or Password is incorrect", "Login Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        btnLogin.setBounds(173, 165, 89, 23);
        frame.getContentPane().add(btnLogin);
    }

    private void showSessionPage() {
        JFrame sessionFrame = new JFrame();
        sessionFrame.setTitle("Session Page");
        sessionFrame.setSize(400, 300);
        sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JLabel lblWelcome = new JLabel("Welcome to your session!");
        lblWelcome.setBounds(120, 100, 150, 50);
        sessionFrame.getContentPane().setLayout(null);
        sessionFrame.getContentPane().add(lblWelcome);
        sessionFrame.setVisible(true);
    }
}