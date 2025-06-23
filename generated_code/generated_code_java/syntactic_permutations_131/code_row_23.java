import java.io.*;
import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;

@WebServlet(name = "hello", value = "/home")
public class HelloWorld extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
    String name = request.getParameter("name");
    PrintWriter out = response.getWriter();
    out.println("<html><body>");
    out.println("<h1>Hello " + name + "</h1>");
    out.println("</body></html>");
  }
}