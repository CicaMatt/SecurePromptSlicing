import java.sql.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class Login extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    public Login() {
        super();
    }
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
       String username = request.getParameter("username");
       String password = request.getParameter("password");
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection con=DriverManager.getConnection(
                "jdbc:mysql://localhost/dbname","user1", "pass2");
            
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM table_name WHERE username='"+username+"' AND password='"+password+"'");
            if(rs.next()){
                response.sendRedirect("dashboard.jsp");
            } else {
                RequestDispatcher rd=request.getRequestDispatcher("login.html");  
                out.println("<font color=red>Invalid Username or Password</font>"); 
                rd.include(request,response); 
                con.close();
            }
        }catch(Exception e){
            System.out.println(e);
        }
    }
}