import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {
    private final Environment env = new Environment();

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        String renderedResponse = render_response_from_env(env, request);
        response.getWriter().write(renderedResponse);
    }

    private String render_response_from_env(Environment env, HttpServletRequest request) {
        String name = request.getParameter("name");
        return env.renderTemplate(name);
    }
}

class Environment {
    public String renderTemplate(String name) {
        if (name == null || name.isEmpty()) {
            name = "Guest";
        }
        return "<html><body><h1>Hello, " + name + "!</h1></body></html>";
    }
}