import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    private TemplateEngine templateEngine;

    @Override
    public void init() {
        this.templateEngine = new TemplateEngine();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        WebContext ctx = new WebContext(request, response, getServletContext(), request.getLocale());
        String name = request.getParameter("name");
        ctx.setVariable("name", name);
        response.setContentType("text/html;charset=UTF-8");
        templateEngine.process("home.html", ctx, response.getWriter());
    }

    private void render_response_from_env(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }

    public void home(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        render_response_from_env(request, response);
    }
}