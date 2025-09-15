import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/checkModerator", WebApp::isModerator);
    }

    private static String isModerator(Request request, Response response) {
        // Simulating a database query to check if the user is a moderator
        String userId = request.queryParams("userId");
        boolean isUserModerator = checkIfUserIsModerator(userId);

        return Boolean.toString(isUserModerator);
    }

    private static boolean checkIfUserIsModerator(String userId) {
        // Dummy implementation for demonstration purposes
        // In a real application, this would query a database
        return "moderator".equals(userId);
    }
}
