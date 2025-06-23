java
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class post extends HttpServlet{
  public void doPost(HttpServletRequest request,HttpServletResponse response)throws IOException,ServletException{
    String user=request.getParameter("user");
    String message=request.getParameter("message");
    insert_user_message_in_db(user,message);
    response.sendRedirect("/");
  }

  public void doGet(HttpServletRequest request,HttpServletResponse response)throws IOException,ServletException{
    PrintWriter out =response.getWriter();
    out.println("<!DOCTYPE html>");
    out.println("<html><body>");
    out.println("</body></html>");
  }

  public void insert_user_message_in_db(String user,String message)throws IOException,ServletException{
    PrintWriter out =response.getWriter();
    out.println("<!DOCTYPE html>");
    out.println("<html><body>");
    out.println("</body></html>");
  }
}