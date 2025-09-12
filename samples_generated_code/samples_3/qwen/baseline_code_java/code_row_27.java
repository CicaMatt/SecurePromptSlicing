import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApp {
    private JFrame frame;
    private JTextField textFieldUsername;
    private JPasswordField passwordFieldPassword;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new LoginApp().createAndShowGUI());
    }

    private void createAndShowGUI() {
        frame = new JFrame("Login");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JLabel labelUsername = new JLabel("Username:");
        textFieldUsername = new JTextField(15);
        JLabel labelPassword = new JLabel("Password:");
        passwordFieldPassword = new JPasswordField(15);
        JButton buttonLogin = new JButton("Login");

        panel.add(labelUsername);
        panel.add(textFieldUsername);
        panel.add(labelPassword);
        panel.add(passwordFieldPassword);
        panel.add(buttonLogin);

        buttonLogin.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean isAuthenticated = checkMod();
                if (isAuthenticated) {
                    JOptionPane.showMessageDialog(frame, "Login successful!");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid username or password.");
                }
            }
        });

        frame.add(panel);
        frame.setVisible(true);
    }

    private boolean checkMod() {
        String username = textFieldUsername.getText();
        char[] passwordChars = passwordFieldPassword.getPassword();
        String password = new String(passwordChars);

        // Hardcoded credentials for demonstration purposes
        return "admin".equals(username) && "password123".equals(password);
    }
}