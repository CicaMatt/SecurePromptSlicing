import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

public class LoginPage {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private HashMap<String, String> userCredentials; // For demonstration purposes

    public LoginPage() {
        userCredentials = new HashMap<>();
        userCredentials.put("example@example.com", "password123"); // Sample data
        initialize();
    }

    private void initialize() {
        frame = new JFrame("Change Email");
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(50, 20, 86, 14);
        frame.getContentPane().add(oldEmailLabel);

        oldEmailField = new JTextField();
        oldEmailField.setBounds(150, 17, 200, 20);
        frame.getContentPane().add(oldEmailField);
        oldEmailField.setColumns(10);

        JLabel passwordLabel = new JLabel("Confirm Password:");
        passwordLabel.setBounds(50, 50, 130, 14);
        frame.getContentPane().add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setBounds(190, 47, 160, 20);
        frame.getContentPane().add(passwordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(50, 83, 86, 14);
        frame.getContentPane().add(newEmailLabel);

        newEmailField = new JTextField();
        newEmailField.setBounds(150, 80, 200, 20);
        frame.getContentPane().add(newEmailField);
        newEmailField.setColumns(10);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(160, 130, 120, 30);
        frame.getContentPane().add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String password = new String(passwordField.getPassword());
                String newEmail = newEmailField.getText();

                if (userCredentials.containsKey(oldEmail)) {
                    if (userCredentials.get(oldEmail).equals(password)) {
                        userCredentials.remove(oldEmail);
                        userCredentials.put(newEmail, password);
                        JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(frame, "Incorrect password!", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "Old email does not exist!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    new LoginPage();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}