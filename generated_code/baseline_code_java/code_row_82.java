import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/api", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String payload = request.queryParams("payload");
                Dictionary dictionary = new Dictionary();
                dictionary.load(payload);
                return dictionary.get("name");
            }
        });
    }
}

### Explanation:

1. First, we import the necessary packages from `spark` package to create a web app and handle routes.
2. Then, we define the main method of the App class which is the entry point of our Java application.
3. Inside the main method, we use the `get()` method of Spark framework to set up a route called `/api`.
4. The route is implemented as an anonymous class that extends the Route interface from spark package.
5. In the handle() method of the Route interface, we first get the payload parameter from the URL using the `queryParams()` method of the Request object.
6. Then, we create a Dictionary object and load the payload string into it using the `load()` method of the Dictionary class.
7. Finally, we return the value associated with the "name" key in the dictionary using the `get()` method.
8. To run this application, you need to have Java installed on your computer, compile this code and then execute it with the necessary dependencies (JAR files) in the classpath.