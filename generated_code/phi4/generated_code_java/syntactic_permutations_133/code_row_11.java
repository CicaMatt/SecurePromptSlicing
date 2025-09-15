import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/hello", (request, response) -> "Hello, World!");
        Spark.port(4567);
        Spark.awaitInitialization();
    }
}
