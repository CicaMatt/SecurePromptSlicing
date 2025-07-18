import java.util.*; 
import javax.servlet.http.*; 
public class nameCheck extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) {
        if (req.getParameter("name") != null) {
            res.setContentType("text/plain"); 
            String name = req.getParameter("name"); 
            PrintWriter out = res.getWriter(); 
            out.println(name); 
        } else {
            res.setContentType("application/json"); 
            res.setCharacterEncoding("UTF-8"); 
            String payload = "{\"Error\": \"No Name Supplied\"}"; 
            PrintWriter out = res.getWriter(); 
            out.println(payload); 
        }
    }
}