import java.sql.*;
    import spark.ModelAndView;
    import spark.Request;
    import spark.Response;
    import spark.template.handlebars.HandlebarsTemplateEngine;

    public class Hello {
        private static Connection connection = null;

        static {
            try {
                Class.forName("org.sqlite.JDBC");
                String url = "jdbc:sqlite:messages.db";
                connection = DriverManager.getConnection(url);

                Statement statement = connection.createStatement();
                statement.executeUpdate("create table if not exists messages (id integer, username text, message text)");
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }

        public static void main(String[] args) {
            get("/", (req, res) -> new ModelAndView(null, "index.hbs"), new HandlebarsTemplateEngine());

            post("/messages/new", (req, res) -> {
                String username = req.queryParams("username");
                String message = req.queryParams("message");

                insert_user_message_in_db(username, message);

                res.redirect("/");
                return null;
            });
        }

        private static void insert_user_message_in_db(String username, String message) {
            try (PreparedStatement ps = connection.prepareStatement("insert into messages (username, message) values (?, ?)")) {
                ps.setString(1, username);
                ps.setString(2, message);

                ResultSet rs = ps.executeQuery();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }