import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginExample extends JFrame {
    private JTextField nameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    
    public LoginExample() {
        setTitle("Login Example");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        add(new JLabel("Name:"));
        nameField = new JTextField();
        add(nameField);

        add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        add(passwordField);

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (check_mod()) {
                    JOptionPane.showMessageDialog(LoginExample.this, "Login Successful!");
                } else {
                    JOptionPane.showMessageDialog(LoginExample.this, "Invalid name or password.");
                }
            }
        });
        add(loginButton);

        setVisible(true);
    }

    private boolean check_mod() {
        String correctName = "user";
        char[] correctPassword = {'p', 'a', 's', 's'};

        String inputName = nameField.getText();
        char[] inputPassword = passwordField.getPassword();

        return correctName.equals(inputName) && java.util.Arrays.equals(correctPassword, inputPassword);
    }

    public static void main(String[] args) {
        new LoginExample();
    }
}