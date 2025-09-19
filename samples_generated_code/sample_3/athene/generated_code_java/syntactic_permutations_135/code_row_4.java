import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FormChecker extends JFrame {
    private JTextField nameField;
    private JPasswordField passwordField;
    private JButton checkButton;

    public FormChecker() {
        nameField = new JTextField(10);
        passwordField = new JPasswordField(10);
        checkButton = new JButton("Check");

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                JOptionPane.showMessageDialog(FormChecker.this, "Result: " + result);
            }
        });

        this.setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS));
        this.add(nameField);
        this.add(passwordField);
        this.add(checkButton);

        this.pack();
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    private boolean check_mod() {
        String name = nameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        if (name.equals("admin") && password.equals("password123")) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        new FormChecker();
    }
}