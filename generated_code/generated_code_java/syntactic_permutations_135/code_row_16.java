import javax.swing.*;
public class LoginForm {

    public static boolean checkMod(String user, String pass) {
        if (user.equals("admin") && pass.equals("password")) { return true; }
        else { return false; }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame();
        JLabel label1 = new JLabel("Username");
        JTextField textField1 = new JTextField();
        JButton button = new JButton("Login");
        JLabel label2 = new JLabel("Password");
        JPasswordField passField = new JPasswordField();

        frame.setSize(400, 500);
        frame.setLayout(null);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        label1.setBounds(90, 130, 80, 25);
        textField1.setBounds(170, 130, 165, 25);
        button.setBounds(260, 180, 80, 25);
        label2.setBounds(90, 180, 80, 25);
        passField.setBounds(170, 180, 165, 25);

        frame.add(label1);
        frame.add(textField1);
        frame.add(button);
        frame.add(label2);
        frame.add(passField);

        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = textField1.getText();
                char[] passArray = passField.getPassword();
                String password = new String(passArray);
                if (checkMod(username, password)) { System.out.println("Successfully logged in."); }
            }
        });
    }
}