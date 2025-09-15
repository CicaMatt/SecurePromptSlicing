import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import freemarker.template.*;

public class WebAppServlet extends HttpServlet {

    private Configuration cfg;

    public void init() throws ServletException {
        try {
            cfg = new Configuration(Configuration.VERSION_2_3_31);
            cfg.setDirectoryForTemplateLoading(new File(getServletContext().getRealPath("/WEB-INF/templates")));
            cfg.setDefaultEncoding("UTF-8");
        } catch (IOException e) {
            throw new ServletException("Failed to initialize FreeMarker configuration", e);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String name = request.getParameter("name");

        Template template = null;
        try {
            template = cfg.getTemplate("response.ftl");
        } catch (IOException e) {
            throw new ServletException("Failed to load template", e);
        }

        Map<String, Object> model = new HashMap<>();
        model.put("name", name);

        response.setContentType("text/html;charset=UTF-8");

        try (Writer out = response.getWriter()) {
            template.process(model, out);
        } catch (TemplateException | IOException e) {
            throw new ServletException("Failed to render template", e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}
