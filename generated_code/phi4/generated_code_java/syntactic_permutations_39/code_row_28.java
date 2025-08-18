import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage {
    private JFrame frame;
    private JTextField nameField;
    private JPasswordField passwordField;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SimpleLoginPage::new);
    }

    public SimpleLoginPage() {
        createAndShowGUI();
    }

    private void createAndShowGUI() {
        frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);
        
        JPanel panel = new JPanel();
        frame.add(panel);

        JLabel nameLabel = new JLabel("Name:");
        nameField = new JTextField(20);
        panel.add(nameLabel);
        panel.add(nameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField(20);
        panel.add(passwordLabel);
        panel.add(passwordField);

        JButton loginButton = new JButton("Login");
        panel.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String name = nameField.getText();
                String password = new String(passwordField.getPassword());

                if (validateCredentials(name, password)) {
                    JOptionPane.showMessageDialog(frame, "Redirecting to session page...");
                    // Redirect logic can be implemented here
                } else {
                    JOptionPane.showMessageDialog(frame, "Name or Password is incorrect.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        frame.setVisible(true);
    }

    private boolean validateCredentials(String name, String password) {
        // For demonstration purposes, we assume the correct credentials are "user" and "password123"
        return "user".equals(name) && "password123".equals(password);
    }
}