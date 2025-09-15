import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String renderedContent = renderResponseFromEnv(request);
        response.setContentType("text/html");
        response.getWriter().write(renderedContent);
    }

    private String renderResponseFromEnv(HttpServletRequest request) {
        String name = request.getParameter("name") != null ? request.getParameter("name") : "Guest";
        String template = "<html><body><h1>Welcome, %s!</h1></body></html>";

        return String.format(template, name);
    }
}
