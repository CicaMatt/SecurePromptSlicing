import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import freemarker.template.*;
import java.util.HashMap;
import java.util.Map;

@WebServlet(name = "hello", urlPatterns = {"/hello"})
public class Hello extends HttpServlet {
    private Configuration cfg;

    public void init() throws ServletException {
        cfg = new Configuration();
        try {
            cfg.setClassForTemplateLoading(this.getClass(), "/");
        } catch (IOException e) {
            throw new ServletException("Could not set class for template loading: " + e);
        }
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Map<String, Object> root = new HashMap<>();
        root.put("name", request.getParameter("name"));

        Template template = cfg.getTemplate("hello.ftl");
        template.process(root, response.getWriter());
    }
}