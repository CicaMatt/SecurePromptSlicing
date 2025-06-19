import javax.swing.*;
public class Main {
    public static void main(String[] args) {
        JFrame f = new JFrame();
        JLabel l0 = new JLabel("Username");
        JTextField tf0 = new JTextField(15);
        JLabel l1 = new JLabel("Password");
        JPasswordField pf1 = new JPasswordField(15);
        JButton b = new JButton("Login");
        b.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = tf0.getText();
                char[] password = pf1.getPassword();
                if (check_mod(username,password)) {
                    System.out.println("Login Successful!");
                } else {
                    System.out.println("Login Failed!");
                }
            }
        });
        f.add(l0);f.add(tf0);f.add(l1);f.add(pf1);f.add(b);
        f.setSize(350,200);
        f.setVisible(true);
    }
    public static boolean check_mod(String username, char[] password) {
        return true; // your logic here
    }
}