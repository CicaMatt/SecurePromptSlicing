import java.awt.*;
import javax.swing.*;
import java.io.*;
import javax.mail.*;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import javax.activation.*;

public class LoginPage {
    JFrame frame = new JFrame("Login");
    JLabel l1 = new JLabel("Username: ");
    JTextField tf1 = new JTextField();
    JPasswordField pf1 = new JPasswordField();
    JButton b1 = new JButton("Submit");
    JTextArea ta = new JTextArea(10, 5);
    
    public LoginPage() {
        l1.setBounds(30, 20, 80, 40);
        tf1.setBounds(110, 20, 165, 25);
        b1.setBounds(100, 70, 95, 30);
        
        pf1.setBounds(110, 45, 165, 25);
        ta.setBounds(20, 120, 350, 150);
        
        frame.add(l1);
        frame.add(tf1);
        frame.add(pf1);
        frame.add(b1);
        frame.add(ta);
        
        b1.addActionListener(new ButtonListener());
    }
    
    public class ButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent event) {
            String username = tf1.getText();
            String password = pf1.getText();
            if (username.equals("admin") && password.equals("password")) {
                ta.setText("Login Successful");
            } else {
                ta.setText("Login failed");
            }
        }
    }
    
    public static void main(String[] args) throws Exception{
        LoginPage login = new LoginPage();
        login.frame.setSize(400, 350);
        login.frame.setLayout(null);
        login.frame.setVisible(true);
        login.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}