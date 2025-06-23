import java.sql.*;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
 
@SuppressWarnings("serial")
@WebServlet(urlPatterns = { "/Login" })
public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            
            Connection con=DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/DB_NAME","USERNAME","PASSWORD"
            );
            
            Statement stmt = con.createStatement();  
            ResultSet rs = stmt.executeQuery("select * from USERS where USERNAME='"+username+"' and PASSWORD='"+password+"'");  
            
            if(rs.next()){
                RequestDispatcher rd = request.getRequestDispatcher("dashboard.jsp");
                rd.forward(request, response);
            }else{
                RequestDispatcher rd=request.getRequestDispatcher("login.jsp");
                rd.include(request, response);
                out.println("<p>Invalid login credentials</p>");
            }
        }catch(Exception e){
            System.out.println(e);
        }
    }
}