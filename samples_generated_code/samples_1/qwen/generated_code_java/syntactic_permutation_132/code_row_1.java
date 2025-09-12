import java.io.IOException;
import java.io.StringWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    private static final Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);

    public HelloServlet() throws IOException {
        cfg.setClassForTemplateLoading(getClass(), "/templates");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.startsWith("/")) {
            String username = pathInfo.substring(1);
            StringWriter out = new StringWriter();
            try {
                Template template = cfg.getTemplate("hello.html");
                template.process(java.util.Map.of("username", username), out);
                response.setContentType("text/html");
                response.getWriter().write(out.toString());
            } catch (TemplateException e) {
                throw new ServletException("Error processing FreeMarker template", e);
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }
}