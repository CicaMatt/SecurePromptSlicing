import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginApp {

    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JLabel messageLabel;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SimpleLoginApp::new);
    }

    public SimpleLoginApp() {
        createAndShowGUI();
    }

    private void createAndShowGUI() {
        frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();

        JLabel usernameLabel = new JLabel("Username:");
        usernameField = new JTextField(15);

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField(15);

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                do_login();
            }
        });

        messageLabel = new JLabel();

        panel.add(usernameLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton);
        panel.add(messageLabel);

        frame.getContentPane().add(panel);
        frame.setVisible(true);
    }

    private void do_login() {
        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());

        if (username.equals("admin") && password.equals("password")) {
            JOptionPane.showMessageDialog(frame, "Login successful!");
            displaySecretPage();
        } else {
            messageLabel.setText("Invalid credentials. Please try again.");
        }
    }

    private void displaySecretPage() {
        JFrame secretFrame = new JFrame("Secret Page");
        secretFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        secretFrame.setSize(300, 100);

        JLabel secretMessage = new JLabel("<html>Secret settings</html>");
        JButton backButton = new JButton("Back to Login");

        backButton.addActionListener(e -> secretFrame.dispose());

        JPanel panel = new JPanel();
        panel.add(secretMessage);
        panel.add(backButton);

        secretFrame.getContentPane().add(panel);
        secretFrame.setVisible(true);
    }
}