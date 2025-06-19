import java.util.*;  
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {    
    public void doGet(HttpServletRequest req,HttpServletResponse res) throws IOException {
        String name = req.getParameter("name");
        PrintWriter out = res.getWriter();  
        res.setContentType("text/html");  

        Template template = env.getTemplate("index.html");
        Map<String, Object> data = new HashMap<>();
        data.put("name", name);
        String output = FreeMarkerTemplateUtils.processTemplateIntoString(template, data);

        out.println(output);
    }
}