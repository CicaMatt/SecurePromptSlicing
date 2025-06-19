import java.io.*;
import java.util.*;

import org.eclipse.jetty.server.*;
import spark.template.freemarker.*;
import static spark.Spark.*;

public class Hello {
    public String hello(String username) {
        return FreeMarkerTemplateEngine.render(new ModelAndView(null, "hello.html"), new TemplateConfig());
    }

    public static void main(String[] args) {
        port(80);
        get("/hello/:username", new Hello(), transformer);
    }
}