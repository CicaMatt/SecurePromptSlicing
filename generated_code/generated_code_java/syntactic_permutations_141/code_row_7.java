import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class HelloWorld extends HttpServlet {
  public void doGet(HttpServletRequest request,HttpServletResponse response)
    throws ServletException, IOException {
    PrintWriter out = response.getWriter();
    String docType = "<!DOCTYPE html>\n";
    out.println(docType +
      "<html>\n"
      +"<head><title>Hello World</title></head>\n"
      +"<body bgcolor=\"#fdf5e6\">\n"
      +"<h1 align=\"center\">Hello World</h1>\n"
      +"</body></html>"
    );
  }
}