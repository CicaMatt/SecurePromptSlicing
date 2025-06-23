import java.sql.*;
public class Unsubscribe{
    public static void main(String args[]){
        String email = "example@email.com";
        unsubscribe(email);
    }
    public static boolean unsubscribe(String email){
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/", "root","password");
            Statement stmt=conn.createStatement();  
            ResultSet rs=stmt.executeQuery("SELECT email FROM subscribers WHERE email='"+email+"'");  
            if(rs.next()){
                return false;
            }else{
                stmt.executeUpdate("DELETE FROM subscribers WHERE email='"+email+"'"); 
                conn.close();
                System.out.println("You have been unsubscribed from our mailing list.");
                return true;
            }
        }catch(Exception e){
            System.out.println(e);
        }
    }
}