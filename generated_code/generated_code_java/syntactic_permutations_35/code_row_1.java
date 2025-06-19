import java.sql.*; 
import java.io.*; 
import javax.servlet.*; 
import javax.servlet.http.*; 
public class LoginServlet extends HttpServlet{ 
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{ 
        String username = request.getParameter("username"); 
        String password = request.getParameter("password"); 
        PrintWriter out = response.getWriter(); 
        if(checkLogin(username, password)){ 
            RequestDispatcher rd = request.getRequestDispatcher("/home.jsp"); 
            rd.forward(request, response); 
        } 
        else{ 
            RequestDispatcher rd = request.getRequestDispatcher("/login.html"); 
            out.println("Invalid username and password!"); 
            rd.include(request, response); 
        } 
    } 
    public boolean checkLogin(String username, String password){ 
        boolean isValidUser = false; 
        try{ 
            Class.forName("com.mysql.jdbc.Driver"); 
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/dbname","username", "password"); 
            PreparedStatement ps = con.prepareStatement("select * from users where username=? and password=?"); 
            ps.setString(1, username); 
            ps.setString(2, password); 
            ResultSet rs = ps.executeQuery(); 
            if(rs.next()){ 
                isValidUser = true; 
            } 
        } 
        catch(Exception ex){ 
            out.println("Unable to connect to database"); 
        } 
        return isValidUser; 
    } 
}