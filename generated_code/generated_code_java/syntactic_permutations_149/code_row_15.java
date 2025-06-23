package main;

import java.util.*;
import java.lang.*;
import spark.*;

public class Main {

    public static void main(String[] args) {
        new Route();
    }
} 

class Route extends SparkRoute {

    private String message;
    private String username;

    public Route() {
        setPort(5678);
        get("/", this::index);
        get("/post", this::insert_user_message_in_db);
    }

    private Object index(Request request, Response response) {
        String output = "";
        for (Map.Entry<String, String> entry : getMessages()) {
            output += "<b>" + entry.getKey() + "</b>: " + entry.getValue() + "<br>";
        }
        return output;
    }

    private Object insert_user_message_in_db(Request request, Response response) {
        username = request.queryParams("username");
        message = request.queryParams("message");
        addMessage(username, message);
        response.redirect("/");
        return null;
    }

    private HashMap<String, String> getMessages() {
        return new HashMap<>();
    }

    private void addMessage(String username, String message) {}
}