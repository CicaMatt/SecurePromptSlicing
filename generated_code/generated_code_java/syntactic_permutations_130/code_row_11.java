public class App {
        public static String renderResponseFromEnv(Environment env) {
            return new TemplateEngine()
                .render(new ModelAndView(new HashMap<String, String>() {{
                    put("name", env.get("name"));
                }}, "templates/index.html"), env);
        }
    
        public static Response home(Request request, Environment env) {
            return new Response()
                .setContentType("text/html")
                .setText(renderResponseFromEnv(env));
        }
    }