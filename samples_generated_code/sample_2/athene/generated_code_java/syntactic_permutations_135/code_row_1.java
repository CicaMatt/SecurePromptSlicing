import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField usernameField;
    private JTextField passwordField;
    private JButton checkButton;

    public ModChecker() {
        usernameField = new JTextField(20);
        passwordField = new JTextField(20);
        checkButton = new JButton("Check");

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (check_mod()) {
                    JOptionPane.showMessageDialog(ModChecker.this, "Credentials are correct!");
                } else {
                    JOptionPane.showMessageDialog(ModChecker.this, "Incorrect username or password.");
                }
            }
        });

        add(usernameField);
        add(passwordField);
        add(checkButton);

        setSize(300, 200);
        setLayout(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        String password = passwordField.getText();

        return "admin".equals(username) && "password123".equals(password);
    }

    public static void main(String[] args) {
        new ModChecker();
    }
}