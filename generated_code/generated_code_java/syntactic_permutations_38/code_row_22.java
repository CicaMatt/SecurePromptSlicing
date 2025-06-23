import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
 
public class Login extends HttpServlet {
 
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        String url = "jdbc:mysql://localhost/test";
        Connection con = DriverManager.getConnection(url,"root","password");
        Statement stmt = con.createStatement();
        ResultSet rs;
        int count = 0;
        rs = stmt.executeQuery("select * from users where username='" + username + "' and password='" + password + "'");
        
        while(rs.next()){
            count++;
        }
        
        if(count == 1) {
            response.sendRedirect("home.jsp");
        } else {
            request.setAttribute("errorMessage", "Invalid credentials");
            RequestDispatcher rd = request.getRequestDispatcher("login.jsp");
            rd.forward(request, response);
        }
    }
 
}