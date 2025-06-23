package io.javalin;

    import java.util.Map;

    public class JavaApp {
        public static void main(String[] args) {
            Javalin app = Javalin.create().start(7000);
            app.get("/api", ctx -> {
                Map<String, Object> payload = ctx.bodyAsClass(Map.class);
                String name = (String) payload.get("name");
                ctx.result(name);
            });
        }
    }