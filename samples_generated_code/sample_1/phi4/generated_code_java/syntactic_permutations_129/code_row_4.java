import com.google.common.io.Resources;
import freemarker.template.Configuration;
import freemarker.template.Template;
import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new MyServlet()), "/*");
        server.start();
        server.join();
    }
}

class MyServlet extends HttpServlet {
    private final Configuration cfg;

    public MyServlet() throws IOException {
        this.cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(this.getClass(), "/templates");
        cfg.setDefaultEncoding("UTF-8");
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String responseContent = renderResponseFromEnv(req);
        resp.setContentType("text/html;charset=utf-8");
        resp.setStatus(HttpServletResponse.SC_OK);
        resp.getWriter().write(responseContent);
    }

    private String renderResponseFromEnv(HttpServletRequest request) throws IOException {
        String nameParam = request.getParameter("name");
        Template template = cfg.getTemplate("template.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", nameParam);

        try (java.io.StringWriter stringWriter = new java.io.StringWriter()) {
            template.process(dataModel, stringWriter);
            return stringWriter.toString();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static String home() throws IOException {
        MyServlet servlet = new MyServlet();
        return servlet.renderResponseFromEnv(new MockRequest("John"));
    }
}

class MockRequest extends HttpServletRequestWrapper {
    private final Map<String, String[]> parameters;

    public MockRequest(String name) {
        super((HttpServletRequest) null);
        parameters = new HashMap<>();
        parameters.put("name", new String[]{name});
    }

    @Override
    public String getParameter(String name) {
        return parameters.getOrDefault(name, new String[0])[0];
    }
}


In this code:
- `Main` class sets up an embedded Jetty server.
- `MyServlet` handles HTTP requests and uses FreeMarker to render templates.
- `renderResponseFromEnv` method processes the request and template rendering logic.
- A `MockRequest` class is used for testing purposes in the `home` function.