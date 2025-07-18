import java.io.IOException;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.annotation.WebServlet;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;
import org.thymeleaf.templateresolver.ServletContextTemplateResolver;

@WebServlet(name = "home", urlPatterns = "/")
public class HomeController extends HttpServlet {
    private TemplateEngine templateEngine;
    
    public void init() throws ServletException {
        ServletContextTemplateResolver templateResolver = new ServletContextTemplateResolver(getServletConfig().getServletContext());
        templateEngine = new TemplateEngine();
        templateEngine.setTemplateResolver(templateResolver);
    }
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        render_response_from_env(request, response, getServletContext());
    }
    
    public static void render_response_from_env(HttpServletRequest req, HttpServletResponse res, ServletContext env) throws IOException {
        String name = req.getParameter("name");
        WebContext ctx = new WebContext(req, res, req.getServletContext());
        ctx.setVariable("name", name);
        templateEngine.process("home", ctx, res.getWriter());
    }
}