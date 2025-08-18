import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/hello", (req, res) -> "Hello World!");

        post("/greet", (request, response) -> {
            String name = request.queryParams("name");
            return "Hi there, " + name;
        });

        get("/", (req, res) -> indexFunction());

        get("/about", (req, res) -> aboutFunction());
    }

    public static String indexFunction() {
        return "Welcome to the home page!";
    }

    public static String aboutFunction() {
        return "This is the about page.";
    }
}