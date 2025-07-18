import java.sql.Connection;
    import java.sql.PreparedStatement;
    import java.sql.ResultSet;
    import java.util.HashMap;
    import java.util.Map;

    import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;

    public class Post {
        private String username;
        private String message;

        public static ModelAndView post(Request request, Response response) {
            Map<String, Object> model = new HashMap<>();
            String inputUsername = request.queryParams("username");
            String inputMessage = request.queryParams("message");

            try (Connection connection = DB.sql2o.open()) {
                String sql = "INSERT INTO messages (username, message) VALUES (:username, :message);";
                PreparedStatement ps = connection.prepareStatement(sql);
                ps.setString("username", inputUsername);
                ps.setString("message", inputMessage);
                ps.executeUpdate();
            } catch (Exception e) {
                System.out.println(e);
            }
            return new ModelAndView(model, "success.hbs");
        }
    }