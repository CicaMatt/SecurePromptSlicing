import java.util.Map;
import java.util.HashMap;
import spark.*;
public static String render_response_from_env(final Environment env) {
    return new TemplateResponse() {
        public Object handle(Request req, Response res) {
            Map<String, String> params = new HashMap<>();
            params.put("name", req.queryParams("name"));
            return env.getTemplate().render(params);
        }
    };
}
public static Route home() {
    return (req, res) -> render_response_from_env(env);
}