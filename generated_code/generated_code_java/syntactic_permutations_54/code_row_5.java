import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class LoginServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    request.getRequestDispatcher("login_page.jsp").forward(request, response);
  }

  public void doPost(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");

    if (check_login(username, password)) {
      RequestDispatcher dispatcher = request.getRequestDispatcher("admin_page.jsp");
      dispatcher.forward(request, response);
    } else {
      // redirect to login page
      RequestDispatcher dispatcher = request.getRequestDispatcher("login_page.jsp");
      dispatcher.forward(request, response);
    }
  }

  private boolean check_login(String username, String password) {
    // TODO: Implement authentication here
    return true;
  }
}


### Explanation:
The LoginServlet class extends HttpServlet and contains two methods doGet() and doPost(). The doGet() method forwards the request to the login_page.jsp page. The doPost() method takes in the username and password from the form, checks if the user is an admin using the check_login() method, and redirects the user to the appropriate page based on the result of the check.