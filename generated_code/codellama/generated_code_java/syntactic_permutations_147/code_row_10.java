import java.sql.*; 
import spark.ModelAndView; 
import spark.template.handlebars.HandlebarsTemplateEngine; 
import static spark.Spark.*; 
public class Main {  
  public static void main(String[] args) {   
    get("/buy_order", (req, res) -> {     
      String stockName = req.queryParams("stock");     
      int quantity = Integer.parseInt(req.queryParams("quantity"));     
      Connection conn = null;      
      try {        
        conn = DriverManager.getConnection("jdbc:sqlite:stocks.db");        
        PreparedStatement pstmt = 
          conn.prepareStatement("INSERT INTO stock_order (name, quantity) VALUES (?, ?);");        
        pstmt.setString(1, stockName);        
        pstmt.setInt(2, quantity);        
        ResultSet rs = pstmt.executeQuery();     
        res.redirect("/stock_view"); 
      } catch (SQLException ex) {       
        System.err.println("Error: " + ex.getMessage());     
      } finally {       
        if (conn != null) {         
          try {           
            conn.close();         
          } catch (SQLException ex) {           
            System.out.println(ex.getMessage());         
          }       
        }   
      } 
      return new ModelAndView(null, "stock_view");  
    }, new HandlebarsTemplateEngine());}