import java.io.*; 
import javax.servlet.*; 
import javax.servlet.http.*; 
public class HelloWorld extends HttpServlet { 
    public void doGet(HttpServletRequest request,HttpServletResponse response) 
        throws IOException, ServletException{ 
            String username = request.getParameter("username"); 
            PrintWriter out = response.getWriter(); 
            StringBuilder outputbuf = new StringBuilder(); 
            outputbuf.append("<html>"); 
            outputbuf.append("<head><title>Hello " + username + "</title></head>"); 
            outputbuf.append("<body>"); 
            outputbuf.append("<h1>Hello " + username + "</h1>"); 
            outputbuf.append("</body></html>"); 
            response.setContentLength(outputbuf.length()); 
            out.write(outputbuf.toString()); 
            out.close(); 
        } 
}