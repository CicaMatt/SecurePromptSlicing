import java.io.*; 
import java.util.*; 
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*; 
public class Login extends HttpServlet{
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if(login(username, password)){
            RequestDispatcher rd=request.getRequestDispatcher("/HomePage.jsp"); 
            rd.forward(request,response); 
        }else{
            RequestDispatcher rd=request.getRequestDispatcher("/Login.html"); 
            PrintWriter out = response.getWriter(); 
            out.println("<font color=red>Either username or password is wrong.</font>"); 
            rd.include(request,response);
        }
    }
    public boolean login(String username, String password){
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection con= DriverManager.getConnection ("jdbc:mysql://localhost:3306/userdb","root","root");
            PreparedStatement ps=con.prepareStatement("select * from users where username=? and password=?");
            ps.setString(1,username);
            ps.setString(2,password);
            ResultSet rs=ps.executeQuery();
            if(rs.next()){
                return true;
            }else{
                return false;
            }
        }catch(Exception e){
            System.out.println(e);
        }
        return false;
    }
}