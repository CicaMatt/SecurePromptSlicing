import java.sql.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.io.*;

public class Login extends HttpServlet{
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/login", "root", "");
            
            PreparedStatement ps = con.prepareStatement("select * from users where username=? and password=?");
            ps.setString(1, username);
            ps.setString(2, password);
            
            ResultSet rs = ps.executeQuery();
            
            if(rs.next()){
                res.sendRedirect("dashboard.html");
            }else{
                RequestDispatcher rd = req.getRequestDispatcher("login.html");
                rd.forward(req, res);
            }
        }catch(Exception e){}
    }
}