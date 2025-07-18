public class User {
        private String email;
        private String password;
    
        public User(String email, String password) {
            this.email = email;
            this.password = password;
        }
    
        public String getEmail() {
            return this.email;
        }
    }
    
    import javax.swing.*;
    import java.awt.*;
    import java.awt.event.ActionEvent;
    import java.awt.event.ActionListener;
    import java.util.HashMap;
    import java.util.Map;
    
    public class LoginPage {
        private JFrame frame;
        private Map<String, User> users = new HashMap<>();
    
        public void createLoginWindow() {
            // Create the login window and its components
            frame = new JFrame("User Login");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setPreferredSize(new Dimension(320, 180));
    
            // Add the email field and its label to the window
            JLabel emailLabel = new JLabel("Email:");
            final JTextField emailField = new JTextField();
            frame.getContentPane().add(emailLabel, BorderLayout.NORTH);
            frame.getContentPane().add(emailField, BorderLayout.CENTER);
    
            // Add the password field and its label to the window
            JLabel passwordLabel = new JLabel("Password:");
            final JTextField passwordField = new JPasswordField();
            frame.getContentPane().add(passwordLabel, BorderLayout.NORTH);
            frame.getContentPane().add(passwordField, BorderLayout.CENTER);
    
            // Add the login button to the window
            JButton loginButton = new JButton("Login");
            loginButton.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    String email = emailField.getText();
                    String password = passwordField.getText();
    
                    User user = users.get(email);
                    if (user == null || !user.password.equals(password)) {
                        JOptionPane.showMessageDialog(frame, "Incorrect email or password");
                        return;
                    }
    
                    createChangeEmailWindow();
                }
            });
            frame.getContentPane().add(loginButton, BorderLayout.SOUTH);
    
            // Display the login window
            frame.pack();
            frame.setVisible(true);
        }
    
        public void createChangeEmailWindow() {
            JFrame changeEmailFrame = new JFrame("Change Email");
            changeEmailFrame.setPreferredSize(new Dimension(320, 180));
    
            // Add the old email field and its label to the window
            JLabel oldEmailLabel = new JLabel("Old Email:");
            final JTextField oldEmailField = new JTextField();
            changeEmailFrame.getContentPane().add(oldEmailLabel, BorderLayout.NORTH);
            changeEmailFrame.getContentPane().add(oldEmailField, BorderLayout.CENTER);
    
            // Add the new email field and its label to the window
            JLabel newEmailLabel = new JLabel("New Email:");
            final JTextField newEmailField = new JTextField();
            changeEmailFrame.getContentPane().add(newEmailLabel, BorderLayout.NORTH);
            changeEmailFrame.getContentPane().add(newEmailField, BorderLayout.CENTER);
    
            // Add the confirm password field and its label to the window
            JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
            final JTextField confirmPasswordField = new JPasswordField();
            changeEmailFrame.getContentPane().add(confirmPasswordLabel, BorderLayout.NORTH);
            changeEmailFrame.getContentPane().add(confirmPasswordField, BorderLayout.CENTER);
    
            // Add the change email button to the window
            JButton changeEmailButton = new JButton("Change Email");
            changeEmailButton.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    String oldEmail = oldEmailField.getText();
                    String newEmail = newEmailField.getText();
                    String confirmPassword = confirmPasswordField.getText();
    
                    User user = users.get(oldEmail);
                    if (user == null || !user.password.equals(confirmPassword)) {
                        JOptionPane.showMessageDialog(frame, "Incorrect old email or confirm password");
                        return;
                    }
    
                    user.email = newEmail;
                    users.remove(oldEmail);
                    users.put(newEmail, user);
                }
            });
            changeEmailFrame.getContentPane().add(changeEmailButton, BorderLayout.SOUTH);
    
            // Display the change email window
            changeEmailFrame.pack();
            changeEmailFrame.setVisible(true);
        }
    }
    
    public class Main {
        public static void main(String[] args) {
            LoginPage loginPage = new LoginPage();
            loginPage.users.put("example@email.com", new User("example@email.com", "password"));
            loginPage.createLoginWindow();
        }
    }