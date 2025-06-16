import java.io.*; 
import javax.servlet.*; 
import javax.servlet.http.*;
import freemarker.template.*;
import static org.junit.Assert.*;  

public class Home extends HttpServlet {  
    @Override  
    protected void doGet(HttpServletRequest request, HttpServletResponse response)  
            throws ServletException, IOException {  
        String name = request.getParameter("name");
        Template t = cfg.getTemplate("index.ftl");
        t.process(root, out);
    }  
}