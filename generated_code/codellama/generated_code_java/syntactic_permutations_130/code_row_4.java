public class Main {
        public static String renderResponseFromEnv(Environment env) {
            Request request = Request(env);
            String name = request.query().get("name");
            Template template = env.getTemplate("hello.ftl");
            String renderedTemplate = template.render(Map.of("name", name));
            return Response.ok(renderedTemplate).toTextResponse();
        }

        public static Response home() {
            Environment env = new Environment();
            Response response = renderResponseFromEnv(env);
            return response;
        }
    }