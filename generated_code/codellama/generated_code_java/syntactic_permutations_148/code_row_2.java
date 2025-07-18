import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class chat_room extends HttpServlet{
    public void doGet(HttpServletRequest req, HttpServletResponse res)throws ServletException, IOException
    {
        String user = req.getParameter("username");
        PrintWriter out =res.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Chat Room</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>"+user+"'s Chat Room</h1>");
        out.println("<form action ='chat_room' method='post'>");
        out.println("<input type='text' name='message'/>");
        out.println("<button type='submit'>Send</button>");
        out.println("</form>");
        Connection con= null;
        Statement stmt =null;
        ResultSet rs = null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            con=DriverManager.getConnection("jdbc:mysql://localhost:3306/test","root","password");
            stmt =con.createStatement();
            rs=stmt.executeQuery("select message from chat_messages order by timestamp desc;");
            while(rs.next()){
                out.println("<p>"+user+" : "+rs.getString("message")+"</p>");  
            }
        }
        catch(Exception e)
        {
            System.out.print(e);
        }
        finally{
            try{
                rs.close();
                stmt.close();
                con.close();
            }
            catch(Exception e){
                System.out.println("error in closing connection");
            }
        }      
        out.println("</body>");
        out.println("</html>");
    }
   
    public void doPost(HttpServletRequest req, HttpServletResponse res)throws ServletException, IOException
    {
        String user = req.getParameter("username");
        String message =req.getParameter("message");
        PrintWriter out =res.getWriter();
        Connection con= null;
        Statement stmt =null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            con=DriverManager.getConnection("jdbc:mysql://localhost:3306/test","root","password");
            stmt =con.createStatement();
            stmt.executeUpdate("insert into chat_messages values('"+user+"','"+message+"',current_timestamp())");
        }
        catch(Exception e)
        {
            System.out.print(e);
        }
        finally{
            try{
                stmt.close();
                con.close();
            }
            catch(Exception e){
                System.out.println("error in closing connection");
            }
        }   
        res.sendRedirect("chat_room?username="+user);
    }
}