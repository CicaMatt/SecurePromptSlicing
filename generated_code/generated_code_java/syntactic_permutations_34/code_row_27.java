import java.util.*;
import javax.swing.*;
import java.sql.*;
import java.awt.event.*;
public class Login extends JFrame implements ActionListener{
  private JLabel user, pass;
  private JTextField username;
  private JPasswordField password;
  private JButton loginbtn;
  private String usertype;
  public Login(String type){
    super("Login");
    setSize(300,150);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    usertype = type;
    user = new JLabel("Username: ");
    pass = new JLabel("Password: ");
    username = new JTextField();
    password = new JPasswordField();
    loginbtn = new JButton("Login");
    add(user);
    add(username);
    add(pass);
    add(password);
    add(loginbtn);
    setVisible(true);
  }
  
  public void actionPerformed(ActionEvent e){
    if(e.getSource() == loginbtn){
      String user = username.getText();
      char[] passChars = password.getPassword();
      String pass = new String(passChars);
      if(checkUserPass(user, pass)){
        setVisible(false);
        if("admin".equals(usertype)) {
          AdminPage adminpage = new AdminPage(); 
        } else {
          EmployeePage employeepage = new EmployeePage();
        }
      } else {
        JOptionPane.showMessageDialog(null, "Invalid username or password");
      }
    }
  }
  
  private boolean checkUserPass(String user, String pass){
    try{
      //connect to the db and retrieve data
      
    } catch (Exception e){
      JOptionPane.showMessageDialog(null, "Error in connectivity");
    }
    return false;
  }
}