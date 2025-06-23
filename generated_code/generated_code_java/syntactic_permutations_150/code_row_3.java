import java.sql.*;
    import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;
    import static spark.Spark.*;

    public class App {
        static String connectionUrl = "jdbc:postgresql://localhost:5432/mydb";
        static Connection connection;

        public static void main(String[] args) {
            // Connect to the database
            try {
                connection = DriverManager.getConnection(connectionUrl, "user", "password");
            } catch (SQLException e) {
                System.out.println("Unable to connect to db.");
                return;
            }

            // Define the post() function
            post("/messages/new", (request, response) -> {
                String username = request.queryParams("username");
                String message = request.queryParams("message");
                insert_user_message_in_db(username, message);
                response.redirect("/");
                return null;
            });

            // Define the get() function to display the main page
            get("/", (request, response) -> {
                Map<String, Object> model = new HashMap<>();
                List<String[]> messages = select_all_messages();
                model.put("messages", messages);
                return new ModelAndView(model, "index.hbs");
            }, new HandlebarsTemplateEngine());
        }

        // The function to insert a user message into the database
        public static void insert_user_message_in_db(String username, String message) {
            String query = "INSERT INTO messages (username, message) VALUES(?, ?)";
            try {
                PreparedStatement statement = connection.prepareStatement(query);
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
            } catch (SQLException e) {
                System.out.println("Unable to insert user message into db.");
                return;
            }
        }

        // The function to select all messages from the database
        public static List<String[]> select_all_messages() {
            String query = "SELECT * FROM messages";
            try {
                ResultSet results = connection.prepareStatement(query).executeQuery();
                ArrayList<String[]> messages = new ArrayList<>();
                while (results.next()) {
                    String username = results.getString("username");
                    String message = results.getString("message");
                    messages.add(new String[]{username, message});
                }
                return messages;
            } catch (SQLException e) {
                System.out.println("Unable to select all user messages from db.");
                return null;
            }
        }
    }