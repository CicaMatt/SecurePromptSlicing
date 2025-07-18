import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloDecorator implements Filter {
  public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain) throws IOException, ServletException {
    HttpServletRequest request = (HttpServletRequest)req;
    HttpServletResponse response = (HttpServletResponse)res;
    String username = request.getParameter("username");
    RequestDispatcher dispatcher = req.getRequestDispatcher("/hello.html");
    dispatcher.forward(request, response);
  }
}