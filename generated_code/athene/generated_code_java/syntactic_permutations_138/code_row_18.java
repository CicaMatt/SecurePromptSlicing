import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/check-moderator", (req, res) -> {
            String userId = req.queryParams("userId");
            boolean isModerator = checkIfUserIsModerator(userId);
            return String.valueOf(isModerator);
        });
    }

    private static boolean checkIfUserIsModerator(String userId) {
        // Dummy implementation for demonstration
        return "moderator".equals(userId);
    }
}