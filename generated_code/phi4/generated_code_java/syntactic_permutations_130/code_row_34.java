import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.TemplateException;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        response = renderResponseFromEnv(request);
        response.getWriter().write(response.getRenderedTemplate());
    }

    private HttpServletResponse renderResponseFromEnv(HttpServletRequest request)
            throws ServletException, IOException {
        String templateName = "template.ftl";
        
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(this.getClass(), "/WEB-INF/templates");
        
        String nameParam = request.getParameter("name");

        try (HttpServletResponse servletResponse = response) {
            cfg.getTemplate(templateName).process(
                java.util.Collections.singletonMap("name", nameParam), 
                servletResponse.getWriter()
            );
            return servletResponse;
        } catch (TemplateException e) {
            throw new ServletException(e);
        }
    }
}