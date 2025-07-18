import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
public class Solution {
    public static String render_response_from_env(Environment env) {
        Request req = env.request();
        String name = req.name;
        Template template = env.template();
        return Response.render(name, template);
    }
    public static Response home(Env env) {
        render_response_from_env(env);
        return response;
    }
}