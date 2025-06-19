import java.util.*;

    public class Home {
        
        public static String render_response_from_env(Environment env) {
            Request request = Request.get_request();
            String template = env.get_template(request.path);
            return new Response(template.render());
        }

        public static String home() {
            return render_response_from_env(Env.get_env());
        }
    }