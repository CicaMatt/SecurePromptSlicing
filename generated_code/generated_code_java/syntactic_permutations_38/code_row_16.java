import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet{
	protected void doPost(HttpServletRequest request, HttpServletResponse response) 
    throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/userdb", "root", "root"
            );
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("select * from users where username='" + username+"' and password='"+password+"'");
            if(rs.next()){
                response.sendRedirect("dashboard.jsp");
            }else{
                response.sendRedirect("login.jsp");
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}