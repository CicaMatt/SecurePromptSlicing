import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class LoginPage {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private Map<String, String> userDatabase = new HashMap<>();

    public LoginPage() {
        initializeUserDatabase();
        createUI();
    }

    private void initializeUserDatabase() {
        userDatabase.put("user@example.com", "password123");
    }

    private void createUI() {
        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 250);
        frame.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");

        frame.add(oldEmailLabel);
        frame.add(oldEmailField);
        frame.add(newEmailLabel);
        frame.add(newEmailField);
        frame.add(confirmPasswordLabel);
        frame.add(confirmPasswordField);
        frame.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (userDatabase.containsKey(oldEmail)) {
                    if (userDatabase.get(oldEmail).equals(confirmPassword)) {
                        userDatabase.remove(oldEmail);
                        userDatabase.put(newEmail, confirmPassword);
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
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage();
            }
        });
    }
}