import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RegistrationPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton registerButton;

    public RegistrationPage() {
        setTitle("Registration Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        add(new JLabel("Username:"));
        usernameField = new JTextField();
        add(usernameField);

        add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        add(passwordField);

        registerButton = new JButton("Register");
        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] password = passwordField.getPassword();
                
                if (username.isEmpty() || password.length == 0) {
                    JOptionPane.showMessageDialog(RegistrationPage.this, "Username and password cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Password is hashed or encrypted here for security purposes
                String passwordHashed = hashPassword(new String(password));
                
                // Registration logic (e.g., saving to a database)
                System.out.println("Registering User:");
                System.out.println("Username: " + username);
                System.out.println("Password Hash: " + passwordHashed);

                JOptionPane.showMessageDialog(RegistrationPage.this, "User registered successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
            }
        });
        add(registerButton);

        setVisible(true);
    }

    private String hashPassword(String password) {
        // Placeholder for a real hashing mechanism
        return Integer.toHexString(password.hashCode());
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new RegistrationPage();
            }
        });
    }
}