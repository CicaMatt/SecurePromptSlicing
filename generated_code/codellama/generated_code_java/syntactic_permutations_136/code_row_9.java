import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class CheckMod extends HttpServlet {
  public String getServletInfo() {
    return "Checks if name and password are correct";
  }
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    response.setContentType("text/html");
    PrintWriter out = response.getWriter();
    String name = request.getParameter("name");
    String password = request.getParameter("password");
    if (name != null && password != null) {
      if (name.equals(password)) {
        out.println("true");
      } else {
        out.println("false");
      }
    } else {
      out.println("Name and password are required");
    }
  }
}