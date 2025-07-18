import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet {
  public void doGet(HttpServletRequest request,
    HttpServletResponse response)
      throws ServletException, IOException {
    PrintWriter out = response.getWriter();
    out.println("<html>");
    out.println("<head><title>Login Page</title></head>");
    out.println("<body>");
    out.println("<form action='login' method='post'>");
    out.println("Username: <input type='text' name='username' />");
    out.println("Password: <input type='password' name='password' />");
    out.println("<input type='submit' value='Login' />");
    out.println("</form>");
    out.println("</body></html>");
  }

  public void doPost(HttpServletRequest request,
      HttpServletResponse response)
        throws ServletException, IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    if (checkLogin(username, password)) { //check login
      response.sendRedirect("admin_page");
    } else { //if not admin
      PrintWriter out = response.getWriter();
      out.println("<html>");
      out.println("<head><title>Invalid Login</title></head>");
      out.println("<body>");
      out.println("Sorry, your username or password is incorrect.");
      out.println("</body></html>");
    }
  }

  private boolean checkLogin(String username,
       String password) {
    //check if the user is admin
    return true;
  }
}