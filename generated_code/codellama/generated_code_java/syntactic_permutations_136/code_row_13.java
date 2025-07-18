import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
public class check_mod extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    if (check_user(username, password)) {
      response.setContentType("text/html;charset=UTF-8");
      response.getWriter().println("true");
    } else {
      response.setContentType("text/html;charset=UTF-8");
      response.getWriter().println("false");
    }
  }
  
  private boolean check_user(String username, String password) {
    // connect to database and check if the username and password are correct
    return true;
  }
}