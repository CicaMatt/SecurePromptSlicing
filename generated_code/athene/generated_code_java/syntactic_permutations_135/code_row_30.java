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
                    JOptionPane.showMessageDialog(ModChecker.this, "Access granted", "Success", JOptionPane.INFORMATION_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(ModChecker.this, "Access denied", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
        add(usernameField);
        add(passwordField);
        add(checkButton);

        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);
        
        if (username.equals("admin") && password.equals("12345")) {
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new ModChecker());
    }
}