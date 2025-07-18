import java.io.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException{
        res.setContentType("text/plain");
        PrintWriter out = res.getWriter();
        String name = req.getParameter("name");
        if (name != null && !name.isEmpty()) {
            out.println(name);
        } else {
            out.println("Name not found!");
        }
    }
}