import java.io.StringWriter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class WebApp {

    private Configuration cfg;

    public WebApp() {
        cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");
    }

    public void home(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String renderedResponse = render_response_from_env(request, cfg);
        response.setContentType("text/html");
        response.getWriter().write(renderedResponse);
    }

    private String render_response_from_env(HttpServletRequest request, Configuration env) throws Exception {
        Template template = env.getTemplate("template.ftl");
        StringWriter out = new StringWriter();
        template.process(request.getParameterMap(), out);
        return out.getBuffer().toString();
    }
}



import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {

    private WebApp webApp;

    @Override
    public void init() {
        webApp = new WebApp();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            webApp.home(request, response);
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}
