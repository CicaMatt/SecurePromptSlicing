package com.megatron;
import spark.*;

public class App {
    public static void main(String[] args) {
        Spark.port(getHerokuAssignedPort());
        Spark.get("/", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            if (authenticateUser(username, password)) {
                return "true";
            } else {
                return "false";
            }
        });
    }

    public static boolean authenticateUser(String username, String password) {
        // Replace this with your own authentication code.
        return true;
    }

    public static int getHerokuAssignedPort() {
        ProcessBuilder process = new ProcessBuilder();
        if (process.environment().get("PORT") != null) {
            return Integer.parseInt(process.environment().get("PORT"));
        }
        return 4567; //return default port if heroku-port isn't set (i.e. on localhost)
    }
}