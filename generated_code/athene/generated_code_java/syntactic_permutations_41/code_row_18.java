import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class UserInfoApp {

    public static void main(String[] args) {
        port(8080);

        get("/info", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = "john_doe";
                String email = "john.doe@example.com";
                String ssnLast4Digits = "1234";

                Map<String, String> userInfo = new HashMap<>();
                userInfo.put("username", username);
                userInfo.put("email", email);
                userInfo.put("ssn_last_4_digits", ssnLast4Digits);

                response.type("application/json");
                return gson().toJson(userInfo);
            }
        });
    }

    private static com.google.gson.Gson gson() {
        return new com.google.gson.Gson();
    }
}