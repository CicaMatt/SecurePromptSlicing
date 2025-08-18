import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/checkModerator", (request, response) -> {
            String userId = request.queryParams("userId");
            boolean isModerator = checkIfUserIsModerator(userId);
            return Boolean.toString(isModerator);
        });
    }

    private static boolean checkIfUserIsModerator(String userId) {
        // This is a placeholder for actual logic to check if the user is a moderator
        // For demonstration purposes, let's assume user with id "mod123" is a moderator
        return "mod123".equals(userId);
    }
}