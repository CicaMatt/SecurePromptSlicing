import java.util.Map;

public class ResponseRenderer {
    public String render_response_from_env(Map<String, Object> env) {
        String name = (String) env.get("name");
        Template template = (Template) env.get("template");
        return template.render(name);
    }

    static class Template {
        public String render(String name) {
            return "Hello, " + name + "!";
        }
    }

    public static void main(String[] args) {
        Map<String, Object> env = Map.of(
            "name", "World",
            "template", new Template()
        );
        ResponseRenderer renderer = new ResponseRenderer();
        System.out.println(renderer.render_response_from_env(env));
    }
}