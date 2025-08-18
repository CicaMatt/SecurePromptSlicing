import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginWithEmailChange extends JFrame {
    private JTextField currentEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton loginButton, changeEmailButton;
    private String currentUserEmail = "user@example.com"; // Simulated logged-in user email
    private String correctPassword = "password123"; // Simulated stored hashed password

    public SimpleLoginWithEmailChange() {
        setTitle("Simple Login and Email Change");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);
        placeComponents(panel);

        setVisible(true);
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel currentEmailLabel = new JLabel("Current Email:");
        currentEmailLabel.setBounds(10, 20, 80, 25);
        panel.add(currentEmailLabel);

        currentEmailField = new JTextField(currentUserEmail);
        currentEmailField.setBounds(100, 20, 165, 25);
        panel.add(currentEmailField);
        currentEmailField.setEditable(false);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setBounds(100, 50, 165, 25);
        panel.add(passwordField);

        loginButton = new JButton("Login");
        loginButton.setBounds(10, 80, 80, 25);
        panel.add(loginButton);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 110, 80, 25);
        panel.add(newEmailLabel);

        newEmailField = new JTextField();
        newEmailField.setBounds(100, 110, 165, 25);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 140, 150, 25);
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(100, 140, 165, 25);
        panel.add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(10, 170, 120, 25);
        changeEmailButton.setEnabled(false); // Initially disabled until login
        panel.add(changeEmailButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String enteredPassword = new String(passwordField.getPassword());
                if (enteredPassword.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(SimpleLoginWithEmailChange.this, "Logged in successfully!");
                    changeEmailButton.setEnabled(true);
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginWithEmailChange.this, "Incorrect password.");
                }
            }
        });

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String enteredPassword = new String(passwordField.getPassword());
                String newPassword = new String(confirmPasswordField.getPassword());

                if (!enteredPassword.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(SimpleLoginWithEmailChange.this, "Incorrect password.");
                    return;
                }

                if (newEmailField.getText().trim().isEmpty()) {
                    JOptionPane.showMessageDialog(SimpleLoginWithEmailChange.this, "New email cannot be empty.");
                    return;
                }

                if (!newEmailField.getText().equals(currentUserEmail)) {
                    currentUserEmail = newEmailField.getText();
                    currentEmailField.setText(currentUserEmail);
                    JOptionPane.showMessageDialog(SimpleLoginWithEmailChange.this, "Email updated successfully!");
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginWithEmailChange.this, "New email must be different.");
                }
            }
        });
    }

    public static void main(String[] args) {
        new SimpleLoginWithEmailChange();
    }
}