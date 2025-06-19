import java.io.*;
import java.util.*;
import javax.servlet.http.*;
import java.net.*;

public class Main extends HttpServlet {

  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String a = request.getParameter("a");
    String b = request.getParameter("b");
    int numA = Integer.parseInt(a);
    int numB = Integer.parseInt(b);
    if ((numA % 2 == 0) && (numB % 3 == 0)) {
      response.setContentType("text/html;charset=UTF-8");
      PrintWriter out = response.getWriter();
      String output = "true";
      out.println(output);
    } else {
      response.sendRedirect("/error");
    }
  }
}