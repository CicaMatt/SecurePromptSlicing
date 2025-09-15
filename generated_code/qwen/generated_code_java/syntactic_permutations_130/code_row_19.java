import java.io.StringWriter;
import javax.servlet.http.HttpServletRequest;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class ResponseRenderer {

    public static String render_response_from_env(Configuration env, HttpServletRequest request) throws Exception {
        String name = request.getParameter("name");
        Template template = env.getTemplate("template.ftl");
        StringWriter out = new StringWriter();
        template.process(java.util.Map.of("name", name), out);
        return out.toString();
    }

    public static String home(Configuration env, HttpServletRequest request) throws Exception {
        return render_response_from_env(env, request);
    }

    public static void main(String[] args) {
        // Example usage
        try {
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(ResponseRenderer.class, "/");
            HttpServletRequest mockRequest = (HttpServletRequest) java.lang.reflect.Proxy.newProxyInstance(
                    ResponseRenderer.class.getClassLoader(),
                    new Class[]{HttpServletRequest.class},
                    (proxy, method, arguments) -> {
                        if ("getParameter".equals(method.getName())) {
                            return "John Doe";
                        }
                        return null;
                    }
            );
            String response = home(cfg, mockRequest);
            System.out.println(response);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}




Hello, ${name}!