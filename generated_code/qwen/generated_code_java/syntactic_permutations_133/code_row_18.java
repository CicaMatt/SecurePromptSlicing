import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/hello", (req, res) -> "Hello, World!");
        Spark.init();
    }
}


This code uses the Spark framework to create a simple web application in Java. The `Spark.get` method is used as a decorator to associate the URL `/hello` with the function that returns the message "Hello, World!". The `Spark.init()` method runs the application. To run this code, you need to have the Spark library included in your project dependencies.