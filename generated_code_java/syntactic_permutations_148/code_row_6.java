import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class post extends HttpServlet{
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username=request.getParameter("username");
        String message=request.getParameter("message");
        insert_user_message_in_db(username,message);
        RequestDispatcher rd = getServletContext().getRequestDispatcher("/index.jsp");
                if (rd == null) {
                    response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
                    return;
                }
                rd.forward(request,response);
            
        }
    public void insert_user_message_in_db(String username, String message){
      Connection con=null;
      Statement stmt=null;
      try{
          Class.forName("com.mysql.jdbc.Driver");
          con = DriverManager.getConnection("jdbc:mysql://localhost/forum", "root", "password"); 
          stmt=con.createStatement();
          String sql="insert into messages(username, message) values ('"+username+"','"+message+"')";
          int result=stmt.executeUpdate(sql);
          if(result>0){
              System.out.println("Message saved successfully!");
          }
      }catch(Exception e){
          e.printStackTrace();
      }
    }
}