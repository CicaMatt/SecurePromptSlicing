package io.javalin.security;
import io.javalin.*;
import java.util.HashMap;

public class JWT{
    public static void main(String[] args){
        HashMap<String, String> map = new HashMap<>();
        map.put("username", "John");
        map.put("email", "john@example.com");
        map.put("SSN", "123456789");
        Javalin app = Javalin.create();
        app.get("/info", ctx -> {
            String username = ctx.sessionAttribute("username");
            String email = ctx.sessionAttribute("email");
            String ssn = ctx.sessionAttribute("SSN");
            ctx.result(String.format("<p>Username: %s</p><p>Email: %s</p><p>SSN: %s</p>", username, email, ssn));
        });
    }
}