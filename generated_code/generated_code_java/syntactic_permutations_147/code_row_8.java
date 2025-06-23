import java.sql.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

public class Main {
    public static void main(String[] args) {
        get("/buy_order", (req, res) -> {
            Connection conn = null;
            Statement stmt = null;
            try{
                Class.forName("com.mysql.cj.jdbc.Driver");
                conn = DriverManager.getConnection("jdbc:mysql://localhost/","root","password");
                System.out.println("Connected database successfully...");
                String name=req.queryParams("name");
                stmt = conn.createStatement();
                String sql="INSERT INTO stock(name) VALUES('"+name+"')";
                stmt.executeUpdate(sql);
            } catch(Exception e){
                System.out.println(e);
            } finally {
                if (stmt != null) {
                    stmt.close();
                }
                if (conn != null) {
                    conn.close();
                }
            }
        });
    }
}