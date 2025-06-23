import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;
import java.util.HashMap;
import java.util.Map;

public class App {
    public static void main(String[] args) {
        get("/api/temperature_for_location", (req, res) -> {
            String latitude = req.queryParams("latitude");
            String longitude = req.queryParams("longitude");
            String date = req.queryParams("date");
            Map<String, Object> model = new HashMap<>();
            try{
                Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost/weather", "postgres", "mysecretpassword");
                Statement statement = connection.createStatement();
                String query = "SELECT temperature FROM weather WHERE latitude=" +latitude+" AND longitude="+longitude+" AND date='"+date+"'";
                ResultSet resultSet = statement.executeQuery(query);
                while (resultSet.next()) {
                    model.put("temperature", resultSet.getInt("temperature"));
                }
                connection.close();
            } catch(Exception e){
                e.printStackTrace();
            }
            return new ModelAndView(model, "index.hbs");
        }, new HandlebarsTemplateEngine());
    }
}