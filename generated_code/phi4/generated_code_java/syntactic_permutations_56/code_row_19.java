import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLogin extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    
    public SimpleLogin() {
        setTitle("Simple Login Page");
        setSize(300, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        add(new JLabel("Username:"));
        usernameField = new JTextField();
        add(usernameField);

        add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        add(passwordField);

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);
        
        JButton loginButton = new JButton("Login/Change Email");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] password = passwordField.getPassword();
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (username.equals("user") && new String(password).equals("password")) { // Replace with real user validation
                    if (!oldEmail.isEmpty() && !newEmail.isEmpty() && !newEmail.equals(oldEmail)) {
                        if (java.util.Arrays.equals(password, confirmPassword)) {
                            JOptionPane.showMessageDialog(SimpleLogin.this,
                                    "Email changed successfully!",
                                    "Success",
                                    JOptionPane.INFORMATION_MESSAGE);
                            oldEmailField.setText("");
                            newEmailField.setText("");
                            confirmPasswordField.setText("");
                        } else {
                            JOptionPane.showMessageDialog(SimpleLogin.this,
                                    "Passwords do not match.",
                                    "Error",
                                    JOptionPane.ERROR_MESSAGE);
                        }
                    } else if (newEmail.equals(oldEmail)) {
                        JOptionPane.showMessageDialog(SimpleLogin.this,
                                "New email must be different from old email.",
                                "Error",
                                JOptionPane.ERROR_MESSAGE);
                    } else {
                        JOptionPane.showMessageDialog(SimpleLogin.this,
                                "Old and new email fields cannot be empty.",
                                "Error",
                                JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(SimpleLogin.this,
                            "Invalid username or password.",
                            "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        
        add(loginButton);

        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new SimpleLogin();
            }
        });
    }
}