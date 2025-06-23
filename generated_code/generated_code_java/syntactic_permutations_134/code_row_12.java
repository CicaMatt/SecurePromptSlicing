import java.net.*;  
import java.io.*;  
import javax.servlet.*;

@WebServlet(urlPatterns = {"/hello/*"}) 
public class HelloWorld extends HttpServlet {  
  private static final long serialVersionUID = 1L;  
    public void service(HttpServletRequest req, HttpServletResponse res) throws IOException{  
        String name = req.getPathInfo();  
        PrintWriter out = res.getWriter();
        out.println("<h1>Hello " + name + "</h1>");  
    }  
}