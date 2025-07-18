import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws IOException, ServletException {
    RequestDispatcher view = request.getRequestDispatcher("login.jsp");
    view.forward(request, response);
  }

  public void doPost(HttpServletRequest request, HttpServletResponse response)
      throws IOException, ServletException {
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    if (username.equals("admin") && password.equals("1234")) {
      RequestDispatcher view = request.getRequestDispatcher("admin_page.jsp");
      view.forward(request, response);
    } else {
      response.sendRedirect("login.jsp?error=true");
    }
  }
}