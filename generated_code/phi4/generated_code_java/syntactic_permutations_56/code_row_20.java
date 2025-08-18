import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginAndChangeEmail {
    private JFrame frame;
    private JTextField usernameField, oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private static final String USERNAME = "user";
    private static final String PASSWORD = "password123";
    private static final String EMAIL = "oldemail@example.com";

    public LoginAndChangeEmail() {
        frame = new JFrame("Login and Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel userLabel = new JLabel("Username:");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        usernameField = new JTextField(20);
        usernameField.setBounds(100, 20, 165, 25);
        panel.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 50, 165, 25);
        panel.add(passwordField);

        JButton loginButton = new JButton("Login");
        loginButton.setBounds(10, 80, 80, 25);
        panel.add(loginButton);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(10, 110, 80, 25);
        
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 140, 80, 25);
        
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 170, 120, 25);

        oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 110, 165, 25);

        newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 140, 165, 25);

        confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(100, 170, 165, 25);

        JButton changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(10, 200, 120, 25);

        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (USERNAME.equals(username) && PASSWORD.equals(password)) {
                    panel.add(oldEmailLabel);
                    panel.add(newEmailLabel);
                    panel.add(confirmPasswordLabel);

                    panel.add(oldEmailField);
                    panel.add(newEmailField);
                    panel.add(confirmPasswordField);
                    
                    panel.add(changeEmailButton);
                    panel.revalidate();
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid credentials");
                }
            }
        });

        changeEmailButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (EMAIL.equals(oldEmail) && !newEmail.isEmpty() && !newEmail.equals(oldEmail)) {
                    if (PASSWORD.equals(newPassword)) {
                        JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(frame, "Incorrect password.");
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Old email incorrect or new email is the same as old.");
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new LoginAndChangeEmail();
            }
        });
    }
}