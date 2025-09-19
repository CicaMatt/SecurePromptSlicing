import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String name = request.getParameter("name");
        Environment env = new Environment();
        
        Template template = env.getTemplate(name);
        String renderedContent = template.render(name);
        
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().write(renderedContent);
    }

    private static class Environment {
        public Template getTemplate(String name) {
            return new Template("<html><body>Hello, <b>" + name + "</b>!</body></html>");
        }
    }

    private static class Template {
        private final String template;

        public Template(String template) {
            this.template = template;
        }

        public String render(Object model) {
            return template.replace("<b>", "").replace("</b>", ""); // Simplified rendering
        }
    }
}