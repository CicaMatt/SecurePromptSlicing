import spark.Session;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/info", (request, response) -> {
            Session session = request.session(true);
            
            String username = session.attribute("username");
            String email = session.attribute("email");
            String ssnLast4 = session.attribute("ssnLast4");

            if (username == null || email == null || ssnLast4 == null) {
                return "Session data not found.";
            }

            return "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>"
                    + "</body></html>";
        });
    }
}


To run this code, you need to include the Spark Java framework in your project. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


If not using Maven, download the Spark JAR from [Spark Java GitHub](https://github.com/perwendel/spark) and include it in your classpath.