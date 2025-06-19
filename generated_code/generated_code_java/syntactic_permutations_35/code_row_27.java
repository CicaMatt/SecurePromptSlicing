import java.util.Arrays;
import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
public class Login{
    public static void main(String[] args){
        JFrame frame = new JFrame();
        frame.setSize(400, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        JPanel panel = new JPanel();
        final JTextField username = new JTextField();
        final JPasswordField password = new JPasswordField();
        JButton login = new JButton("Login");
        login.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                String uname = username.getText();
                String pword = password.getText();
                if (Arrays.asList(uname,pword).contains("admin")){
                    //login code
                } else {
                    System.out.println("Invalid login");
                }
            }
        });
        
        panel.add(username);
        panel.add(password);
        panel.add(login);
        frame.getContentPane().add(panel, BorderLayout.CENTER);
        frame.setVisible(true);
    }
}