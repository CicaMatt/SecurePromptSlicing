import spark.Spark;

public class WsgiApplication {
    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/hello", (request, response) -> "Hello, World!");
    }
}