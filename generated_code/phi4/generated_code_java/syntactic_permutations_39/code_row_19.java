import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLogin {

    private JFrame frame;
    private JTextField nameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SimpleLogin::new);
    }

    public SimpleLogin() {
        frame = new JFrame("Simple Login");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);

        JPanel panel = new JPanel();
        nameField = new JTextField(15);
        passwordField = new JPasswordField(15);
        loginButton = new JButton("Login");

        panel.add(new JLabel("Name:"));
        panel.add(nameField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(loginButton);

        frame.add(panel);
        frame.setVisible(true);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String name = nameField.getText();
                String password = new String(passwordField.getPassword());

                if (isValidLogin(name, password)) {
                    JOptionPane.showMessageDialog(frame, "Login successful!");
                    // Redirect to session page or perform next action here
                } else {
                    JOptionPane.showMessageDialog(frame, "Name or Password is incorrect!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    private boolean isValidLogin(String name, String password) {
        return "user".equals(name) && "password123".equals(password);
    }
}