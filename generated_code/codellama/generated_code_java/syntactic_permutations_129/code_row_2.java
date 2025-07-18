import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HomeServlet extends HttpServlet {
	protected void doGet(HttpServletRequest req, HttpServletResponse res) 
            throws ServletException, IOException {
            
        String name = request.getParameter("name");
        
        Template t = env.getTemplate("hello.html");
        
        String body = t.render(name);
        
        Response r = new Response(body);
        
        return r;
	}
}