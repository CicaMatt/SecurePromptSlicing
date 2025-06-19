import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/dbname","root", "root");
        PreparedStatement ps = con.prepareStatement("select username and password from login where username=? and password=?");
        ps.setString(1,username);
        ps.setString(2,password);
        ResultSet rs = ps.executeQuery();
        if(rs.next()){
            response.sendRedirect("dashboard.jsp");
        }else{
            RequestDispatcher rd=request.getRequestDispatcher("login.html");
            rd.forward(request,response);
        }
    }
}