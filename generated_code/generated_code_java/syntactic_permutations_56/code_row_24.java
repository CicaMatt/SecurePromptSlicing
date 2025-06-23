// imports
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class LoginPage {
    // variables
    private JFrame frame;
    private JPanel panel;
    private JLabel title, emailLabel, passwordLabel;
    private JTextField emailField;
    private JPasswordField passwordField;
    private JButton loginButton, changeEmailButton;
    private String email, password;

    // constructor
    public LoginPage() {
        createGUI();
    }

    // create GUI method
    private void createGUI() {
        frame = new JFrame("Login Page");
        panel = new JPanel(new GridBagLayout());
        title = new JLabel("Login Page");
        emailLabel = new JLabel("Email: ");
        passwordLabel = new JLabel("Password: ");
        emailField = new JTextField(20);
        passwordField = new JPasswordField(20);
        loginButton = new JButton("Login");
        changeEmailButton = new JButton("Change Email");

        // add components to panel
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.HORIZONTAL;

        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.insets = new Insets(15, 15, 15, 15);
        panel.add(title, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.insets = new Insets(15, 15, 15, 15);
        panel.add(emailLabel, gbc);

        gbc.gridx = 1;
        gbc.gridy = 1;
        gbc.insets = new Insets(15, 15, 15, 15);
        panel.add(emailField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.insets = new Insets(15, 15, 15, 15);
        panel.add(passwordLabel, gbc);

        gbc.gridx = 1;
        gbc.gridy = 2;
        gbc.insets = new Insets(15, 15, 15, 15);
        panel.add(passwordField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.insets = new Insets(15, 15, 15, 15);
        panel.add(loginButton, gbc);

        gbc.gridx = 1;
        gbc.gridy = 3;
        gbc.insets = new Insets(15, 15, 15, 15);
        panel.add(changeEmailButton, gbc);

        // add panel to frame and set frame properties
        frame.add(panel);
        frame.setSize(400, 200);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);

        // add listeners to buttons
        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent event) {
                email = emailField.getText();
                password = new String(passwordField.getPassword());
                if (email != null && password != null) {
                    System.out.println("Logged in successfully!");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid username or password!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        changeEmailButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent event) {
                if (email != null && password != null) {
                    String newEmail = JOptionPane.showInputDialog("Enter your new email: ");
                    String confirmPassword = JOptionPane.showInputDialog("Confirm your password: ");

                    if (newEmail != null && confirmPassword != null) {
                        System.out.println("Your email has been changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(frame, "Invalid new email or confirmation password!", "Error",
                                JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "You must be logged in to change your email!", "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}