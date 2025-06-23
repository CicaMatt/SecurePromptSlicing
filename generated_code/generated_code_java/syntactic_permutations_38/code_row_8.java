import javax.servlet.annotation.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import com.mysql.cj.jdbc.exceptions.MysqlDataTruncation;
import java.sql.*;
@WebServlet("/login")
public class LoginPage extends HttpServlet{
    private String url = "jdbc:mysql://localhost:3306/user";
    private String uName = "root";
    private String pass = "";
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        PrintWriter out = response.getWriter();
        out.println("<form action='login' method='post'>");
        out.println("Username:<input type='text' name='username'><br>");
        out.println("Password:<input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection(url, uName, pass);
            String uname = request.getParameter("username");
            String pwd = request.getParameter("password");
            PreparedStatement ps = conn.prepareStatement("select * from login where username=? and password=?;");
            ps.setString(1, uname);
            ps.setString(2, pwd);
            ResultSet rs = ps.executeQuery();
            if (rs.next()){
                response.sendRedirect("dashboard");
            } else {
                request.setAttribute("message","Invalid username or password.");
                RequestDispatcher rd = request.getRequestDispatcher("login");
                rd.forward(request,response);
            }
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}