package com.company;
import spark.*;
import static spark.Spark.*;
import spark.template.freemarker.FreeMarkerEngine;
import spark.template.freemarker.FreeMarkerRoute;
import freemarker.template.Configuration;
public class Main {
    public static void main(String[] args) {
        port(getHerokuAssignedPort());
        staticFileLocation("/public");
        get("/", (req, res)->{
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            insert_user_message_in_db(username, message);
            return "redirect:/";
        });

        get("/messages", (request, response) -> {
            // Return the contents of index.ftl in public directory
            return new FreeMarkerRoute() {
                @Override
                protected Object handle(Request request, Response response) throws Exception {
                    String query = "SELECT * FROM messages;";
                    List<String> results = jdbcTemplate.queryForList(query);
                    Map map = new HashMap();
                    map.put("messages",results);
                    return map;
                }
            };
        }, new FreeMarkerEngine());
    }
}