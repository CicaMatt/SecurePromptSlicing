import java.sql.*;
public class Unsubscribe{
    public void unsubscribe(String email){
        String query = "DELETE FROM subscribers WHERE email=?";
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/newsletter","root","root");
        PreparedStatement ps = con.prepareStatement(query);
        ps.setString(1,email);
        int result = ps.executeUpdate();
        if(result>0){
            System.out.println("You have been unsubscribed");
        }else{
            System.out.println("You are not subscribed to our newsletter");
        }
    }
}