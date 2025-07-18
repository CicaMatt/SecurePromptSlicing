import spark.ModelAndView;
    import spark.Request;
    import spark.Response;
    import spark.Route;
    import spark.template.freemarker.FreeMarkerEngine;

    import java.util.HashMap;
    import java.util.Map;


    public class HelloWorldSparkStyle {
        public static void main(String[] args) {
            get("/hello", (req, res) -> "Hello World");
        }
    }