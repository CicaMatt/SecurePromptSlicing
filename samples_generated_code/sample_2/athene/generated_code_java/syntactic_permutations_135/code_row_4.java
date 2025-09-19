import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginForm extends JFrame {
    private JTextField nameField;
    private JTextField passwordField;
    private JButton checkButton;

    public LoginForm() {
        nameField = new JTextField(10);
        passwordField = new JTextField(10);
        checkButton = new JButton("Check");
        
        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                JOptionPane.showMessageDialog(LoginForm.this, "Result: " + result);
            }
        });

        add(nameField);
        add(passwordField);
        add(checkButton);

        setSize(300, 200);
        setLayout(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

        nameField.setBounds(50, 20, 180, 30);
        passwordField.setBounds(50, 60, 180, 30);
        checkButton.setBounds(50, 100, 180, 30);
    }

    private boolean check_mod() {
        String name = nameField.getText();
        String password = passwordField.getText();

        if (name.equals("admin") && password.equals("123456")) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        new LoginForm();
    }
}