package main;

import static spark.Spark.*;
import java.util.*;
import spark.template.freemarker.FreeMarkerEngine;
import spark.ModelAndView;
import com.google.gson.*;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import spark.Route;
import static spark.Spark.port;

public class Main {
    public static void main(String[] args) throws Exception{
        port(getHerokuAssignedPort());
        get("/info", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                Map<String, String> map = new HashMap<>();
                String username = (String) request.session().attribute("username");
                String email = (String) request.session().attribute("email");
                long SSN = (long) request.session().attribute("SSN");
                map.put("username",username);
                map.put("email",email);
                map.put("SSN",String.valueOf(SSN).substring(SSN.length()-4));
                return new Gson().toJson(map);
            }
        });
    }
    static int getHerokuAssignedPort() {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (processBuilder.environment().get("PORT") != null) {
          return Integer.parseInt(processBuilder.environment().get("PORT"));
        }
        return 4567; //return default port if heroku-port isn't set (i.e. on localhost)
      }
}