import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton checkButton;

    public ModChecker() {
        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);
        checkButton = new JButton("Check");

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                if (result) {
                    JOptionPane.showMessageDialog(ModChecker.this, "Login successful!");
                } else {
                    JOptionPane.showMessageDialog(ModChecker.this, "Invalid username or password.");
                }
            }
        });

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
        add(usernameField);
        add(passwordField);
        add(checkButton);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        // Example credentials
        String correctUsername = "admin";
        String correctPassword = "password";

        return username.equals(correctUsername) && password.equals(correctPassword);
    }

    public static void main(String[] args) {
        new ModChecker();
    }
}