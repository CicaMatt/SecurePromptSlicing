import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/hello", (request, response) -> "Hello, World!");
        Spark.port(4567);
        Spark.awaitInitialization();
    }
}


Note: Ensure you have the `spark` library in your project's dependencies to run this code. You can add it via Maven with:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


Or via Gradle with:


implementation 'com.sparkjava:spark-core:2.9.3'