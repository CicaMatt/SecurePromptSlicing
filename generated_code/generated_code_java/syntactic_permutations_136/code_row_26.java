import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class ServletExample extends HttpServlet {
  public void doGet(HttpServletRequest request,
                    HttpServletResponse response)
            throws ServletException, IOException {

    String username = request.getParameter("username");
    String password = request.getParameter("password");

    if (check_mod(username, password)) {
      PrintWriter out = response.getWriter();
      out.println("<p>Username and Password correct</p>");
    }
  }
  private boolean check_mod(String username, String password) {
    if (username != null && password != null) {
      return true;
    } else {
      return false;
    }
  }
}