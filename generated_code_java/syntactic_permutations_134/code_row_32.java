import java.io.*;
import java.net.*;
import java.util.*;

public class MyApplication implements Router {
    private Map<String, Route> routes = new HashMap<>();

    public MyApplication() {
        addRoute("/hello/{username}", this::hello);
    }

    public void addRoute(String url, Function<Map<String, String>, String> func) {
        this.routes.put(url, new Route(url, func));
    }

    private String hello(Map<String, String> params) {
        return "Hello " + escape(params.get("username"));
    }

    private String escape(String str) {
        // TODO
    }
}