import java.sql.*;
import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "Login", urlPatterns = {"/login"})
public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/dbname","root","");
            Statement stmt = con.createStatement();
            
            ResultSet rs = stmt.executeQuery("SELECT username,password FROM users WHERE username='" +username+"' and password='"+password+"'");
            if(rs.next()){
                response.sendRedirect("dashboard.jsp");
            } else {
                response.sendRedirect("login.html");
            }
        } catch(Exception e){
            e.printStackTrace();
        }
    }
}