import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

class User {
    private String email;
    private String password;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }
}

public class EmailChangeApp extends JFrame {
    private static User loggedInUser;

    public EmailChangeApp(User user) {
        loggedInUser = user;
        setTitle("Email Change Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        JTextField oldEmailField = new JTextField(15);
        JTextField newEmailField = new JTextField(15);
        JPasswordField confirmPasswordField = new JPasswordField(15);
        
        JButton submitButton = new JButton("Change Email");
        
        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);

        panel.add(submitButton);
        add(panel);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!oldEmail.equals(loggedInUser.getEmail())) {
                    JOptionPane.showMessageDialog(null, "Old email must match the current email.");
                    return;
                }

                if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(null, "New email must be different from old email.");
                    return;
                }

                if (!loggedInUser.checkPassword(confirmPassword)) {
                    JOptionPane.showMessageDialog(null, "Incorrect password.");
                    return;
                }

                loggedInUser.setEmail(newEmail);
                JOptionPane.showMessageDialog(null, "Email changed successfully!");
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            User user = new User("oldemail@example.com", "password123");
            EmailChangeApp frame = new EmailChangeApp(user);
            frame.setVisible(true);
        });
    }
}