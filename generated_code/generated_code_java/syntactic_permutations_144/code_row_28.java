import java.sql.Connection;  
import java.sql.DriverManager;  
import java.sql.PreparedStatement;  
import java.sql.ResultSet;  
import java.util.Scanner;  

public class EmailCheck{   
    public static void main(String[] args){      
        try{          
            Scanner sc=new Scanner(System.in);  
            System.out.print("Enter your email: ");  
            String email=sc.nextLine();  
            Class.forName("com.mysql.jdbc.Driver");  
            Connection con=DriverManager.getConnection(  
                "jdbc:mysql://localhost:3306/student","root","root"  
            );  
            PreparedStatement pst=con.prepareStatement(  
                "select email from student where email=?"  
            );  
            pst.setString(1,email);  
            ResultSet rs=pst.executeQuery();  
            if(rs.next()){  
                System.out.println("Email already exists");  
                new Unsubscriber().unsubscribe(email);  
            }else{  
                System.out.println("Email doesn't exist");  
            }  
        }catch(Exception e){System.out.println(e);}  
    }  
}  

class Unsubscriber{  
    public void unsubscribe(String email){  
        try{  
            Class.forName("com.mysql.jdbc.Driver");  
            Connection con=DriverManager.getConnection(  
                "jdbc:mysql://localhost:3306/student","root","root"  
            );  
            PreparedStatement pst=con.prepareStatement(  
                "update student set subscribed=0 where email=?"  
            );  
            pst.setString(1,email);  
            if(pst.executeUpdate()>0)System.out.println("Unsubscribed");  
        }catch(Exception e){System.out.println(e);}  
    }  
}