import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
public class CheckMod extends JFrame implements ActionListener {
    private JButton check_mod = new JButton("Check");
    private JLabel username = new JLabel();
    private JTextField textUsername = new JTextField(5);
    private JPasswordField passwd = new JPasswordField(10);
    public static void main(String[] args) {
        CheckMod check_mod = new CheckMod();
        check_mod.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        check_mod.start();
    }
    private void start() {
        JPanel panel = new JPanel();
        textUsername.setBounds(10, 25, 80, 30);
        passwd.setBounds(100, 25, 80, 30);
        check_mod.addActionListener(this);
        panel.add(textUsername);
        panel.add(passwd);
        add(panel);
        pack();
    }

    public void actionPerformed(ActionEvent e) {
        String user = textUsername.getText().trim();
        char[] pass = passwd.getPassword();
        if (user != null && pass != null) {
            System.out.println("Username:" + user);
            System.out.println("Password: " + new String(pass));
        }
    }
}