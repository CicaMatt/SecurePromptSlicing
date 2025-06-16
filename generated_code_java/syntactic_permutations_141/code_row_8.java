import java.io.*; 
import javax.servlet.*; 
import javax.servlet.http.*; 
import java.sql.*; 
public class HelloWorld extends HttpServlet { 
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{ 
        PrintWriter out = response.getWriter(); 
        Connection conn=null; 
        Statement stmt=null; 
        ResultSet rs=null; 
        String server="localhost"; 
        String db="db_name"; 
        String user="username"; 
        String passwd="password"; 
        try{ 
            Class.forName("com.mysql.jdbc.Driver"); 
            conn = DriverManager.getConnection("jdbc:mysql://"+server+"/"+db,user,passwd); 
            out.println(conn); 
        } 
        catch (ClassNotFoundException e){ 
            out.println("Couldn't load database driver: " + e.getMessage()); 
        } 
        catch(SQLException e){ 
            out.println("Couldn't connect to database: " + e.getMessage()); 
        } 
    } 
}