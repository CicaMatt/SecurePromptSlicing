import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.mysql.jdbc.PreparedStatement;
import java.sql.DriverManager;
import java.util.*;

public class PostMessage {
    public static void post(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
        String user = req.getParameter("username");
        String message = req.getParameter("message");
        insert_user_message_in_db(user, message);
        res.sendRedirect("/mainpage");
    }
    
    public static void insert_user_message_in_db(String user, String message){
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/webchat","root","password");
            PreparedStatement ps=con.prepareStatement("insert into messages (username,message) values(?,?)");
            ps.setString(1, user);
            ps.setString(2, message);
            ps.executeUpdate();
        }catch(Exception e){}
    }
}