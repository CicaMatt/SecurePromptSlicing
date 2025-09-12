import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApp {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Login");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel userLabel = new JLabel("Name:");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        JTextField userNameText = new JTextField(20);
        userNameText.setBounds(100, 20, 165, 25);
        panel.add(userNameText);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        JPasswordField passwordText = new JPasswordField(20);
        passwordText.setBounds(100, 50, 165, 25);
        panel.add(passwordText);

        JButton button = new JButton("Login");
        button.setBounds(10, 80, 80, 25);
        panel.add(button);

        ActionListener actionListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String name = userNameText.getText();
                String password = new String(passwordText.getPassword());

                boolean isValidUser = checkMod(name, password);
                if (isValidUser) {
                    JOptionPane.showMessageDialog(null, "Login Successful");
                } else {
                    JOptionPane.showMessageDialog(null, "Invalid Name or Password");
                }
            }
        };

        button.addActionListener(actionListener);
    }

    private static boolean checkMod(String name, String password) {
        // Example credentials for demonstration
        return "user".equals(name) && "pass123".equals(password);
    }
}