import java.util.*;

public class Code {
    
    public static String render_response_from_env(Environment env, Request req) {
        Map<String, Object> context = new HashMap<>();
        context.put("name", req.args("name"));
        Template temp = env.getTemplate("index.html");
        String rendered = temp.render(context);
        return Response.ok(rendered).build();
    }

    public static void main(String[] args) {
        System.out.println(home());
    }

    public static Response home() {
        Environment env = new Environment();
        Request req = new Request();
        return render_response_from_env(env, req);
    }
}