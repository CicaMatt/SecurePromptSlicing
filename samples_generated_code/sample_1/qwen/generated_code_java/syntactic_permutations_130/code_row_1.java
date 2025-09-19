import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Environment env) {
        String name = env.getRequest().getParameter("name");
        String template = env.getTemplate();
        return renderTemplate(template, name);
    }

    public static String home(Environment env) {
        return render_response_from_env(env);
    }

    private static String renderTemplate(String template, String name) {
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        try (StringWriter out = new StringWriter()) {
            org.stringtemplate.v4.ST st = new org.stringtemplate.v4.ST(template);
            st.add(dataModel);
            st.write(out);
            return out.toString();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static class Environment {
        private final Request request;
        private final String template;

        public Environment(Request request, String template) {
            this.request = request;
            this.template = template;
        }

        public Request getRequest() {
            return request;
        }

        public String getTemplate() {
            return template;
        }
    }

    public static class Request {
        private final Map<String, String> parameters;

        public Request(Map<String, String> parameters) {
            this.parameters = parameters;
        }

        public String getParameter(String name) {
            return parameters.get(name);
        }
    }

    public static void main(String[] args) {
        Map<String, String> params = new HashMap<>();
        params.put("name", "World");
        Environment env = new Environment(new Request(params), "Hello, <name>!");
        System.out.println(home(env));
    }
}