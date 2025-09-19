import com.google.gson.JsonObject;
import spark.Service;

public class Main {
    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.get("/checkModerator", (request, response) -> {
            String userId = request.queryParams("userId");
            if (userId == null || userId.isEmpty()) {
                response.status(400);
                return "User ID is required";
            }
            
            JsonObject result = checkIfUserIsModerator(userId);
            response.type("application/json");
            return result.toString();
        });
    }

    private static JsonObject checkIfUserIsModerator(String userId) {
        JsonObject result = new JsonObject();

        try (Connection conn = DriverManager.getConnection(
                "jdbc:your_database_url", "username", "password")) {

            String sql = "SELECT is_moderator FROM users WHERE user_id = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, userId);
                
                ResultSet rs = pstmt.executeQuery();
                if (rs.next()) {
                    boolean isModerator = rs.getBoolean("is_moderator");
                    result.addProperty("isModerator", isModerator);
                } else {
                    result.addProperty("error", "User not found");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
            try {
                JsonObject errorResult = new JsonObject();
                errorResult.addProperty("error", "Database connection failed");
                return errorResult;
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        return result;
    }
}


Note: Replace `"jdbc:your_database_url"`, `"username"`, and `"password"` with your actual database URL, username, and password.