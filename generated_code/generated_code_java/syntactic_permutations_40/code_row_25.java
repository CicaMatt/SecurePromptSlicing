import java.util.*;
import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;
import static spark.Spark.*;

public class HelloWorld {
    public static void main(String[] args) {
        port(8080);
        get("/", (req, res) -> "Hello World");
    }
}