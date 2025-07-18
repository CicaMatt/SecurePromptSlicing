import java.io.*;
import javax.servlet.*;
public class HelloServlet implements Servlet { 
    public void service(ServletRequest req, ServletResponse res) throws ServletException, IOException { 
        String username = req.getParameter("username"); 
        PrintWriter out = res.getWriter(); 
        StringBuilder outputBuf = new StringBuilder(); 
        outputBuf.append("<html> <body> <h1>Hello " + username + "</h1> </body> </html>"); 
        out.println(outputBuf); 
        out.close(); 
    }
}