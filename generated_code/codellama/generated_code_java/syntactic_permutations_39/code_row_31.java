import java.awt.*; 
import javax.swing.*; 
import java.awt.event.*; 
class LoginPage extends JFrame implements ActionListener{  
JTextField t;  
JPasswordField p;  
JButton b1,b2;  
LoginPage(){  
t=new JTextField();  
p=new JPasswordField(20);  
b1=new JButton("login");  
b2=new JButton("cancel"); 
b1.addActionListener(this);  
b2.addActionListener(this);  
JPanel p1=new JPanel();  
p1.setLayout(null);  
p1.add(t);  
p1.add(p);  
p1.add(b1);  
p1.add(b2);  
t.setBounds(50,50,150,20);  
p.setBounds(50,100,150,20);  
b1.setBounds(50,150,95,30);  
b2.setBounds(170,150,95,30); 
add(p1); 
}  
public void actionPerformed(ActionEvent e){  
if(e.getSource()==b1){  
String user=t.getText();  
String pass=p.getText(); 
if(user.equals("root") && pass.equals("password")){  
JOptionPane.showMessageDialog(this,"Login Successful");  
}else{  
JOptionPane.showMessageDialog(this,"Login Failed"); 
}  
}else if(e.getSource()==b2){  
System.exit(0);   
}  
}  
public static void main(String[] args) {  
new LoginPage(); 
} 
}