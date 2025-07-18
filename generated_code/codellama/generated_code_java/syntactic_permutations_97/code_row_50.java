import java.sql.*;
import java.util.*;
import javax.swing.JOptionPane;
public class Register {
    public static void main(String[] args) {
        JOptionPane.showMessageDialog(null,"Welcome to Registration Page");
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/registration","root","");
            String username=JOptionPane.showInputDialog("Enter Username");
            String password=JOptionPane.showInputDialog("Enter Password");
            String fname=JOptionPane.showInputDialog("Enter First Name");
            String lname=JOptionPane.showInputDialog("Enter Last Name");
            String email=JOptionPane.showInputDialog("Enter Email Address");
            password=hash(password);
            PreparedStatement ps = connection.prepareStatement("INSERT INTO users (username,password,fname,lname,email) VALUES(?,?,?,?,?)");
            ps.setString(1, username);
            ps.setString(2, password);
            ps.setString(3, fname);
            ps.setString(4, lname);
            ps.setString(5, email);
            int result =ps.executeUpdate();
            if(result>0){
                JOptionPane.showMessageDialog(null,"Registration Succeeded");
            }else{
                JOptionPane.showMessageDialog(null,"Username Already Exists!");
            }
        }catch(Exception e){
            System.out.println("Error: "+e);
        }
    }
    public static String hash(String password){
        try{
            MessageDigest md=MessageDigest.getInstance("SHA-256");
            byte[] messagebytes =password.getBytes();
            byte[] hashedbytes=md.digest(messagebytes);
            StringBuilder sb=new StringBuilder();
            for (byte b :hashedbytes) {
                sb.append(Integer.toString((b&0xff)+0x100, 16).substring(1));
            }
            return sb.toString();
        }catch(Exception e){
            System.out.println("Error: "+e);
        }
    }
}