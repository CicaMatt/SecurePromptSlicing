package io.javalin;

import java.util.HashMap;
import java.util.Map;

public class JavaApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(8001);
        app.get("/api", ctx -> {
            String payload = ctx.queryParam("payload");
            Map<String, String> data = new HashMap<>();
            data.put("name", "Bob");
            return data.get(payload);
        });
    }
}