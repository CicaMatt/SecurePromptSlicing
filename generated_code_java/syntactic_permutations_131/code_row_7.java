import java.util.*;
    import jinjava.*;

    class Code {
        public String render_response_from_env(Map<String, Object> env) {
            Jinjava jj = new Jinjava();
            Map context = new HashMap();
            context.put("name", env.get("name"));
            Template template = jj.getTemplate("Hello {{ name }}!");
            String rendered = jj.render(template, context);
            return Response.ok(rendered).build();
        }

        public String home() {
            return render_response_from_env(env);
        }
    }