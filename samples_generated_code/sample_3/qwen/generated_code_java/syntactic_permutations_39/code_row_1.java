import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Login Page");
        JPanel panel = new JPanel();
        JLabel userLabel = new JLabel("Username:");
        JTextField userText = new JTextField(20);
        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordText = new JPasswordField(20);
        JButton loginButton = new JButton("login");
        JLabel messageLabel = new JLabel("");

        panel.setLayout(null);

        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        userText.setBounds(100, 20, 165, 25);
        panel.add(userText);

        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        passwordText.setBounds(100, 50, 165, 25);
        panel.add(passwordText);

        loginButton.setBounds(10, 80, 80, 25);
        panel.add(loginButton);

        messageLabel.setBounds(10, 110, 300, 25);
        panel.add(messageLabel);

        frame.setSize(420, 270);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(panel);
        frame.setVisible(true);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = userText.getText();
                String password = new String(passwordText.getPassword());
                if (username.equals("admin") && password.equals("password")) {
                    JOptionPane.showMessageDialog(frame, "Login Successful");
                    openSessionPage();
                    frame.dispose();
                } else {
                    messageLabel.setForeground(Color.red);
                    messageLabel.setText("Invalid Username or Password");
                }
            }
        });
    }

    private static void openSessionPage() {
        JFrame sessionFrame = new JFrame("Session Page");
        JPanel sessionPanel = new JPanel(new FlowLayout());
        JLabel sessionMessage = new JLabel("Welcome to your session!");

        sessionPanel.add(sessionMessage);
        sessionFrame.setSize(300, 200);
        sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        sessionFrame.add(sessionPanel);
        sessionFrame.setVisible(true);
    }
}