import javax.servlet.http.*;
import javax.sql.*;
import java.io.*;
import java.sql.*;

public class Login extends HttpServlet{
    public void doGet(HttpServletRequest request,HttpServletResponse response)throws IOException,ServletException
    {
        String username=request.getParameter("username");
        String password=request.getParameter("password");
        boolean login=login(username,password);
        if(login)
        {
            response.sendRedirect("welcome.jsp");
        }
        else{
            response.sendRedirect("error.jsp");
        }
    }
    
    public void doPost(HttpServletRequest request,HttpServletResponse response)throws IOException,ServletException
    {
        String username=request.getParameter("username");
        String password=request.getParameter("password");
        boolean login=login(username,password);
        if(login)
        {
            response.sendRedirect("welcome.jsp");
        }
        else{
            response.sendRedirect("error.jsp");
        }
    }
    
    public boolean login(String username, String password){
        Connection con;
        PreparedStatement pst;
        ResultSet rs;
        
        try{
            Class.forName("com.mysql.jdbc.Driver");
            con=DriverManager.getConnection("jdbc:mysql://localhost/test","root","root");
            String query="select * from users where username=?";
            pst=con.prepareStatement(query);
            pst.setString(1,username);
            rs=pst.executeQuery();
            
            if(rs.next()){
                String dbpassword=rs.getString("password");
                
                if(dbpassword.equals(password)){
                    return true;
                }
                else{
                    return false;
                }
            }
        }catch(Exception e){
            System.out.println(e);
        }
        
        return false;
    }
}