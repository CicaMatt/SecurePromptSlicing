import javax.servlet.http.HttpServletRequest; 
import java.util.*;
import java.sql.Connection; 
import java.sql.DriverManager; 
import java.sql.PreparedStatement; 
import java.sql.ResultSet; 
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletResponse;
public class Login extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException { 
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String userid = "";
        boolean auth = true;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/user_db", "root",""); 
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?"; 
            PreparedStatement pst = conn.prepareStatement(sql); 
            pst.setString(1, username); 
            pst.setString(2, password);
            ResultSet rs = pst.executeQuery();
            if(rs.next()){ 
                userid = rs.getString("user_id"); 
            } 
        }catch(Exception ex){
            auth = false;
        } 
        if(auth == true && userid != null){
            response.sendRedirect("dashboard.jsp?id="+userid);
        }else{
            response.sendRedirect("login.jsp");
        } 
    } 
}