import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
public class BuyOrder {
    public static void main(String[] args) {
        Connection con = null;
        String url = "jdbc:mysql://localhost/stockdb";
        try{ 
            Class.forName("com.mysql.cj.jdbc.Driver");
            con= DriverManager.getConnection(url,"user","password");
            PreparedStatement pst= con.prepareStatement("insert into stock values(?,?)");
            pst.setString(1,stockName); //assuming stockName is a variable with the name of the stock entered by user
            pst.setInt(2,quantity);//assuming quantity is a variable with the quantity of stocks entered by user
            int i = stmt.executeUpdate(); 
        }catch (Exception e) {
            System.out.println(e);
        }finally{
            try {
                if(con != null){
                    con.close();
                }
            } catch (SQLException e) {
                System.out.println("Connection close failed" + e);
            }
        }
    }
}