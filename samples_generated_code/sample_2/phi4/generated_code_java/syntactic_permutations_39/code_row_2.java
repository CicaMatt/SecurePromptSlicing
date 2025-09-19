import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLogin {

    public static void main(String[] args) {
        // Create a frame for the login form
        JFrame frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);

        // Create panels and components for username and password input fields
        JPanel panel = new JPanel();
        JLabel userLabel = new JLabel("Username:");
        JTextField userText = new JTextField(15);
        JLabel passwordLabel = new JLabel("Password:");
        JPasswordField passwordText = new JPasswordField(15);

        // Add components to the panel
        panel.add(userLabel);
        panel.add(userText);
        panel.add(passwordLabel);
        panel.add(passwordText);

        // Create a login button
        JButton loginButton = new JButton("Login");
        frame.getContentPane().add(panel, "North");
        frame.getContentPane().add(loginButton, "South");

        // Set the correct username and password for validation
        String correctUsername = "user";
        String correctPassword = "password";

        // Add action listener to the button for login logic
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = userText.getText();
                String password = new String(passwordText.getPassword());

                if (username.equals(correctUsername) && password.equals(correctPassword)) {
                    // Redirect to session page on successful login
                    JOptionPane.showMessageDialog(frame, "Login Successful! Welcome.");
                    frame.dispose();  // Close the login window

                    JFrame sessionFrame = new JFrame("Session Page");
                    sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                    sessionFrame.setSize(300, 100);

                    JLabel welcomeLabel = new JLabel("Welcome to the Session!");
                    sessionFrame.add(welcomeLabel);

                    sessionFrame.setVisible(true);
                } else {
                    // Show error message on incorrect login
                    JOptionPane.showMessageDialog(frame, "Username or Password is Incorrect.");
                }
            }
        });

        frame.setVisible(true);
    }
}