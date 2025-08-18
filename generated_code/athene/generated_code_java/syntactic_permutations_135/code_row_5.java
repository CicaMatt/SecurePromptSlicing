import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public ModChecker() {
        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);
        loginButton = new JButton("Login");

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean isValid = checkMod(usernameField.getText(), new String(passwordField.getPassword()));
                if (isValid) {
                    JOptionPane.showMessageDialog(ModChecker.this, "Login successful!");
                } else {
                    JOptionPane.showMessageDialog(ModChecker.this, "Invalid username or password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
        add(usernameField);
        add(passwordField);
        add(loginButton);

        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private boolean checkMod(String username, String password) {
        return "admin".equals(username) && "password123".equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new ModChecker().setVisible(true));
    }
}