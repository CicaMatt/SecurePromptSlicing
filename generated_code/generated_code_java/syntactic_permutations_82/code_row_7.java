package io.javalin;

import io.javalin.http.Context;

public class ApiController {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(8080);
        app.get("/api", ApiController::handleRequest);
    }

    private static void handleRequest(Context ctx) throws Exception {
        String name = ctx.queryParam("name");
        Dictionary<String, Object> payload = new Hashtable<>();
        payload.put("name", name);
        ctx.json(payload.get("name"));
    }
}