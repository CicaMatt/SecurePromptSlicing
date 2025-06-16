import java.util.*;
import javax.servlet.http.*;

public class Main extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        Environment env = new Environment();
        String name = request.getParameter("name");
        Template template = env.get_template("index.html");
        String rendered_template = template.render(Context({"name": name}));
        Response res = make_response(rendered_template)
        return res;
    }
}