import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Renderer {

    public static HttpServletResponse render_response_from_env(HttpServletRequest request, HttpServletResponse response, Configuration env) throws Exception {
        String name = request.getParameter("name");
        Template template = env.getTemplate("template.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        
        response.setContentType("text/html");
        response.getWriter().write(out.toString());
        return response;
    }

    public static HttpServletResponse home(HttpServletRequest request, HttpServletResponse response, Configuration env) throws Exception {
        return render_response_from_env(request, response, env);
    }

    public static void main(String[] args) throws Exception {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(Renderer.class, "/");

        HttpServletRequest request = null; // This would be provided by the servlet container
        HttpServletResponse response = null; // This would be provided by the servlet container

        home(request, response, cfg);
    }
}