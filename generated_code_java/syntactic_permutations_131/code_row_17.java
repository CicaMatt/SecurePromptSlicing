import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import freemarker.template.*;
import freemarker.ext.servlet.*;

public class FmHello extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
         Template template = cfg.getTemplate("hello.ftl");
          PrintWriter out = response.getWriter();
           template.process(null, out);
    }
}