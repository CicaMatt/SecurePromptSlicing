import java.sql.*;
import javax.mail.MessagingException;
import com.sendgrid.SendGrid;
public class Unsubscribe {
    private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";  
    private static final String DB_URL = "jdbc:mysql://localhost/mydb";
    private static final String USER = "root";
    private static final String PASS = "root";
    
    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement pst = null;
        try{
            Class.forName(JDBC_DRIVER);
        	conn = DriverManager.getConnection(DB_URL,USER,PASS);
             String sql = "DELETE FROM subscribers WHERE email = ?";
             pst = conn.prepareStatement(sql);
             pst.setString(1,args[0]);
             int count = pst.executeUpdate();
             if(count>0){
                 unsubscribeMailingList(args[0]);
                 System.out.println("User has been deleted and unsubscribed from the mailing list");
             }else{
                 System.out.println("The email is not subscribed");
             }
        }catch(SQLException se){
            se.printStackTrace();
        }catch(Exception e){
            e.printStackTrace();
        }finally{
            try{
                if(pst!=null) pst.close();
                if(conn!=null) conn.close();
            }catch(SQLException se){
                se.printStackTrace();
            }
        }
    }
    
    public static void unsubscribeMailingList(String email) throws MessagingException{
        SendGrid sendgrid = new SendGrid("SENDGRID_APIKEY");
        Request request = new Request();
        request.method = Method.DELETE;
        request.endpoint = "mail/subscribers/"+email;
        Response response = sendgrid.api(request);
    }
}