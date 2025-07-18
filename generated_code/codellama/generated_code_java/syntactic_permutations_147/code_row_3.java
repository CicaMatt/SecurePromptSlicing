import java.sql.*;
import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        staticFileLocation("/public");
        String layout = "{{{body}}}";

        get("/buy_order", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            return new ModelAndView(model,"stock_view.hbs");
        },new HandlebarsTemplateEngine());

        post("/buy_order", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            String stockName= request.queryParams("stock_name");
            int quantity = Integer.parseInt(request.queryParams("quantity"));
            Connection connection = null;
            Statement statement = null;
            ResultSet resultSet = null;
            try {
                Class.forName("org.sqlite.JDBC");
                connection = DriverManager.getConnection("jdbc:sqlite:stocks.db");
                String sql = "INSERT INTO stocks (name, quantity) VALUES(?,?)";
                PreparedStatement preparedStatement=connection.prepareStatement(sql);
                preparedStatement.setString(1, stockName);
                preparedStatement.setInt(2, quantity);
                int result=preparedStatement.executeUpdate();
            } catch (Exception e) {
                model.put("message", "There was an error: " + e.getClass().getName() + ": " + e.getMessage());
            } finally {
                if(connection != null){
                    try{
                        connection.close();
                    } catch (SQLException e) {
                        model.put("message", "There was an error: " + e.getClass().getName() + ": " + e.getMessage());
                    }
                }
            }
            return new ModelAndView(model,"stock_view.hbs");
        },new HandlebarsTemplateEngine());
    }
}