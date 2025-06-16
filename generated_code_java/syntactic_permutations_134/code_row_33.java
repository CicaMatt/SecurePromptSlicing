import java.io.*; 
import javax.servlet.*;  
import javax.servlet.http.*;
@WebServlet(name = "Hello Servlet", urlPatterns = {"/hello/*"})  
public class Hello extends HttpServlet {  
protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {  
    String name = request.getParameter("username"); 
    PrintWriter out = response.getWriter();
    out.println("<html><body>Hello "+ name +"</body></html>"); 
} 
}