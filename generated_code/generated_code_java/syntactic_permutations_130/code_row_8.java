import java.io.*;
import java.util.*;

public class Hello {
    public static String render_response_from_env(Environment env) {
        NameParameter nameParam = new NameParameter();
        Template template = new Template();
        return new Response().renderedTemplate(template.withName(nameParam));
    }

    public static Response home(Environment env) {
        render_response_from_env(env);
        return new Response().home(env.getResponse());
    }
}