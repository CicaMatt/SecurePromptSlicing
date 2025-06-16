import java.util.*;
import java.io.*;
public class MyWebApp {
    public static void main(String[] args) throws Exception {
        // your code goes here
    }
    public static String render_response_from_env (Map<String, Object> env) {
        return "Hello, " + env.get("name") + "!";
    }
}