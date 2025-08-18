import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JPanel loginPanel;
    private JPanel changeEmailPanel;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private boolean isLoggedIn;
    private String correctUsername = "user";
    private String correctPassword = "password";

    public LoginPage() {
        setTitle("Login Page");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new CardLayout());

        initializeLoginPanel();
        initializeChangeEmailPanel();

        add(loginPanel, "login");
        add(changeEmailPanel, "changeEmail");

        changePanel("login");
    }

    private void initializeLoginPanel() {
        loginPanel = new JPanel(new GridLayout(3, 2));
        loginPanel.add(new JLabel("Username:"));
        usernameField = new JTextField();
        loginPanel.add(usernameField);
        loginPanel.add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        loginPanel.add(passwordField);
        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordChars = passwordField.getPassword();
                String password = new String(passwordChars);

                if (username.equals(correctUsername) && password.equals(correctPassword)) {
                    isLoggedIn = true;
                    changePanel("changeEmail");
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Invalid login", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        loginPanel.add(loginButton);
    }

    private void initializeChangeEmailPanel() {
        changeEmailPanel = new JPanel(new GridLayout(4, 2));
        changeEmailPanel.add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        changeEmailPanel.add(newEmailField);
        changeEmailPanel.add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        changeEmailPanel.add(confirmPasswordField);
        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!isLoggedIn) {
                    JOptionPane.showMessageDialog(LoginPage.this, "You must be logged in", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                char[] passwordChars = confirmPasswordField.getPassword();
                String password = new String(passwordChars);
                String newEmail = newEmailField.getText();

                if (!password.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                if (newEmail.isEmpty() || newEmail.equals("old@email.com")) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Enter a valid new email", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
            }
        });
        changeEmailPanel.add(changeEmailButton);
    }

    private void changePanel(String panelName) {
        CardLayout cl = (CardLayout)(getContentPane().getLayout());
        cl.show(getContentPane(), panelName);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}