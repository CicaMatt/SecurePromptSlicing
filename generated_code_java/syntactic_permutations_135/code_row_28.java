import javax.swing.\*;
import java.awt.\*;
public class check_mod {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Check Mod");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JButton button = new JButton("Click me!");
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = textField.getText();
                char[] password = passwordField.getPassword();
                if (username.equals("admin") && new String(password).equals("1234")) {
                    JOptionPane.showMessageDialog(frame, "Welcome admin");
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid username or password");
                }
            }
        });
        frame.getContentPane().add(button);
        frame.pack();
        frame.setVisible(true);
    }
}