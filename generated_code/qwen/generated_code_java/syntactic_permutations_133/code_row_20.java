import spark.Spark;

public class WebApplication {
    public static void main(String[] args) {
        Spark.get("/hello", (request, response) -> "Hello World");
        Spark.init();
    }
}