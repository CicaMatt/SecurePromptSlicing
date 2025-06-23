import spark.Request;
import spark.Response;
import spark.Route;

public class Application {
   public static void main(String[] args) {
       final String username = "john";
       final String email = "johndoe@email.com";
       final String ssn = "123-456-7890";
       
       Route infoRoute = (Request request, Response response) -> {
           return "<html><body>User Info:<br/>username: john<br/>email: johndoe@email.com<br/>ssn: 123-456-7890</body></html>";
       };
       
   }
}