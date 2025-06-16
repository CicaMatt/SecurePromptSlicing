import java.io.*;
import java.util.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    if (login(username, password)) {
      response.sendRedirect("/home");
    } else {
      return;
    }
  }
}