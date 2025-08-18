import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.port(4567);
        
        Spark.get("/info", (request, response) -> {
            String username = "JohnDoe";
            String email = "john.doe@example.com";
            String ssn = "123-45-6789";

            return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        });
    }
}


To run this code, ensure you have the Spark Java framework and its dependencies set up in your project. You can include Spark using Maven:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


Or, if you're using Gradle:


implementation 'com.sparkjava:spark-core:2.9.3'