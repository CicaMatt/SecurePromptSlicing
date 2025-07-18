import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name="LoginPage", urlPatterns={"/login"})
public class LoginPage extends HttpServlet {
  @Override
  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
    String name = request.getParameter("name");
    String password = request.getParameter("password");
    if (name != null && password != null && name.equals("admin") && password.equals("password")) {
      RequestDispatcher dispatcher = request.getRequestDispatcher("/session");
      dispatcher.forward(request, response);
    } else {
      response.sendRedirect("login?error=true");
    }
  }
}