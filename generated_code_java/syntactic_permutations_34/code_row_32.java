import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String name=request.getParameter("name");
        String password=request.getParameter("password");
        
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection con=DriverManager.getConnection("jdbc:mysql://localhost/mydb","root","root");
            PreparedStatement ps=con.prepareStatement("select * from mylogin where name=? and password=?");
            ps.setString(1,name);
            ps.setString(2,password);
            ResultSet rs=ps.executeQuery();
            if(rs.next()){
                RequestDispatcher rd=request.getRequestDispatcher("dashboard.html");
                rd.forward(request,response);
            }
            else{
                response.sendRedirect("login.html");
            }
            con.close();
        }catch(Exception e){e.printStackTrace();}
    out.close();
    }
}