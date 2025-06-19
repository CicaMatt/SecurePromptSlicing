import java.sql.*;

public class BuyStock {
    public static void main(String[] args) {
        String stockName = "";
        int quantity = 0;
        Connection conn = null;
        Statement stmt = null;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL,USER,PASS);
            stmt = conn.createStatement();
        }catch(Exception e){
            System.out.println(e);
        }
    }
}