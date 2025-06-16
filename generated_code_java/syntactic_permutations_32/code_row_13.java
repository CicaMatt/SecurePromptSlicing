package com.main;
import spark.*;
import static spark.Spark.*;
import java.net.URISyntaxException;
import java.util.logging.Logger;
import org.eclipse.jetty.server.Server;
public class Main {
    public static void main(String[] args) throws URISyntaxException {
        port(getHerokuAssignedPort());
        redirect_invalid_url();
    }
    private static int getHerokuAssignedPort() {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (processBuilder.environment().get("PORT") != null) {
            return Integer.parseInt(processBuilder.environment().get("PORT"));
        }
        return 4567; //return default port if heroku-port isn't set (i.e. on localhost)
    }
    public static void redirect_invalid_url() {
        String url = "https://www.google.com";
        try {
            get("/redirect/:url",(req, res)->{
                String input = req.params(":url");
                if (input == null || !input.startsWith("http://example.com")) {
                    Logger.getLogger(Main.class.getName()).info("Redirecting to "+url);
                    res.redirect(url);
                } else {
                    res.status(403);
                    return "Invalid URL";
                }
            });
        } catch (Exception e) {
            Logger.getLogger(Main.class.getName()).info("Error redirecting url");
        }
    }
}