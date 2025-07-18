import java.sql.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
public class Register extends JFrame {
   private static final long serialVersionUID = 1L;
   private JPanel contentPane;
   private JTextField textField;
   private JPasswordField passwordField;
   private JTextField textField_1;
   private JTextField textField_2;
   private JButton btnRegister;
   private String username;
   private String password;
   private String firstname;
   private String lastname;
   private String email;
   
   public Register() {
      setTitle("Register");
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      contentPane = new JPanel();
      contentPane.setBorder(null);
      setContentPane(contentPane);
      contentPane.setLayout(null);
      
      textField = new JTextField();
      textField.setText("Username");
      textField.setBounds(136, 45, 180, 29);
      contentPane.add(textField);
      textField.setColumns(10);
      
      passwordField = new JPasswordField();
      passwordField.setText("password");
      passwordField.setBounds(136, 75, 180, 29);
      contentPane.add(passwordField);
      
      textField_1 = new JTextField();
      textField_1.setText("First Name");
      textField_1.setBounds(136, 104, 180, 29);
      contentPane.add(textField_1);
      textField_1.setColumns(10);
      
      textField_2 = new JTextField();
      textField_2.setText("Last Name");
      textField_2.setBounds(136, 133, 180, 29);
      contentPane.add(textField_2);
      textField_2.setColumns(10);
      
      JButton btnRegister = new JButton("Register");
      btnRegister.addActionListener(new ActionListener() {
         public void actionPerformed(ActionEvent arg0) {
            username = textField.getText();
            password = String.valueOf(passwordField.getPassword());
            firstname = textField_1.getText();
            lastname = textField_2.getText();
            email = JOptionPane.showInputDialog("Enter Email");
            
            //Create database connection
            Connection conn = null;
            try {
               Class.forName("com.mysql.jdbc.Driver").newInstance();
               conn = DriverManager.getConnection("jdbc:mysql://localhost/registration", "root", "");
               
               //Check if the user is already in the database
               PreparedStatement stmnt = conn.prepareStatement("SELECT * FROM users WHERE username=?");
               stmnt.setString(1, username);
               ResultSet rs = stmnt.executeQuery();
               if (rs.next()) {
                  JOptionPane.showMessageDialog(null, "Username Already Exists!");
               } else {
                  //Insert the user into database
                  PreparedStatement stmnt2 = conn.prepareStatement("INSERT INTO users VALUES(?, ?, ?, ?, ?)");
                  stmnt2.setString(1, username);
                  stmnt2.setString(2, password);
                  stmnt2.setString(3, firstname);
                  stmnt2.setString(4, lastname);
                  stmnt2.setString(5, email);
                  int rs2 = stmnt2.executeUpdate();
                  if (rs2 > 0) {
                     JOptionPane.showMessageDialog(null, "Registration Successful!");
                  } else {
                     JOptionPane.showMessageDialog(null, "Failed to Register! Try Again");
                  }
               }
            } catch (Exception e) {
               System.err.println("Got an exception!");
               System.err.println(e.getMessage());
            }
         }
      });
      btnRegister.setBounds(146, 172, 89, 23);
      contentPane.add(btnRegister);
   }
   
   public static void main(String[] args) {
      Register frame = new Register();
      frame.pack();
      frame.setVisible(true);
   }
}