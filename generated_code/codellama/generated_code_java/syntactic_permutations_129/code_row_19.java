import java.io.*;
import javax.servlet.http.*;

public class HomeServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
        render_response_from_env(response,request, env);
    }
    
    public void render_response_from_env(HttpServletResponse response, HttpServletRequest request, Environment env){
        String template = env.getTemplate("index.html");
        String name = request.getParameter("name");
        String rendered = template.render(name);
        response.setContentType("text/html");
        response.getWriter().write(rendered);
    }
    
    public HttpServletResponse home(HttpServletRequest request, Environment env){
        return render_response_from_env(request, env);
    } 
}