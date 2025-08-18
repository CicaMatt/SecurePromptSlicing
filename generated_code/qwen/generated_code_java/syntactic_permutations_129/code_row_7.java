import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class WebApp {

    private Configuration cfg;

    public WebApp() {
        cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(this.getClass(), "/templates");
    }

    public HttpServletResponse render_response_from_env(HttpServletRequest request, Map<String, Object> env) throws Exception {
        String name = request.getParameter("name");
        Template template = (Template) env.get("template");
        
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);

        HttpServletResponse response = WebUtil.createResponse(out.toString());
        return response;
    }

    public HttpServletResponse home(HttpServletRequest request) throws Exception {
        Map<String, Object> env = new HashMap<>();
        Template template = cfg.getTemplate("home.ftl");
        env.put("template", template);
        
        return render_response_from_env(request, env);
    }
}

class WebUtil {
    public static HttpServletResponse createResponse(String content) {
        // This is a mock implementation for demonstration purposes
        // In a real application, you would use a proper HttpServletResponse object
        // and set the appropriate headers and content.
        return new MockHttpServletResponse(content);
    }
}

class MockHttpServletResponse extends HttpServletResponse {
    private String content;

    public MockHttpServletResponse(String content) {
        this.content = content;
    }

    @Override
    public void setStatus(int sc) {}

    @Override
    public void setContentType(String type) {}

    @Override
    public java.io.PrintWriter getWriter() throws java.io.IOException {
        return new java.io.PrintWriter(new java.io.StringWriter());
    }

    @Override
    public String toString() {
        return content;
    }
}