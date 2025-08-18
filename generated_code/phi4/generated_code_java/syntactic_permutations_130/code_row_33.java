import java.io.StringWriter;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {
    private Configuration cfg;

    @Override
    public void init(ServletConfig config) throws ServletException {
        super.init(config);
        try {
            cfg = new Configuration(Configuration.VERSION_2_3_31);
            cfg.setServletContextForTemplateLoading(getServletContext(), "/WEB-INF/templates");
        } catch (Exception e) {
            throw new ServletException("Error initializing FreeMarker configuration", e);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String result = renderResponseFromEnv(request, getServletContext());
        response.setContentType("text/html");
        response.getWriter().write(result);
    }

    private String renderResponseFromEnv(HttpServletRequest request, javax.servlet.ServletContext servletContext) throws IOException, TemplateException {
        String name = request.getParameter("name");
        Template template;
        
        try {
            template = cfg.getTemplate("template.ftl");
        } catch (IOException e) {
            throw new IOException("Error loading template", e);
        }

        java.util.HashMap<String, Object> model = new java.util.HashMap<>();
        model.put("name", name);

        try (StringWriter out = new StringWriter()) {
            template.process(model, out);
            return out.toString();
        }
    }
}


**Note:** Ensure that you have a `template.ftl` file in the `/WEB-INF/templates/` directory. The FreeMarker library should be included as a dependency in your project for this code to work correctly.