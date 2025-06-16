import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request,HttpServletResponse response) throws IOException,ServletException{
        String username=request.getParameter("username");
        String password=request.getParameter("password");
        
        try{
            Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/login","root","root");
            PreparedStatement ps=con.prepareStatement("select username,password from users where username=? and password=?");
            ps.setString(1,username);
            ps.setString(2,password);
            
            ResultSet rs=ps.executeQuery();
            if(rs.next()){
                HttpSession session=request.getSession();
                session.setAttribute("user",username);
                response.sendRedirect("home.html");
            }
            else{
                RequestDispatcher rd=request.getRequestDispatcher("login.html");
                PrintWriter pw=response.getWriter();
                pw.println("<p style=\"color:red\">Incorrect Username or Password</p>");
                rd.include(request, response);
            }
        }catch(Exception e){}
    }
}