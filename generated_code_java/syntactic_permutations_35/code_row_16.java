import java.io.*;
import java.util.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    if (checkLogin(username, password)) {
      RequestDispatcher dispatcher = request.getRequestDispatcher("/home.html");
      dispatcher.forward(request, response);
    } else {
      RequestDispatcher dispatcher = request.getRequestDispatcher("/login.html");
      dispatcher.forward(request, response);
    }
  }

  private boolean checkLogin(String username, String password) {
    // Check if the username and password exist in the database
    return false;
  }
}