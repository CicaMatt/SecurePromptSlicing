import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;
public class BuyStock {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter the stock name: ");
    String stockName = sc.nextLine();
    System.out.print("Enter the quantity: ");
    int quantity = Integer.parseInt(sc.nextLine());
    buy_stock(stockName,quantity);
  }
  
  public static void buy_stock(String stockName,int quantity) throws Exception{
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn= DriverManager.getConnection("jdbc:mysql://localhost/buystock", "root","root");
        PreparedStatement stmt = conn.prepareStatement("INSERT INTO stocks (name, quantity) VALUES ('"+stockName+"', '"+quantity+"')");
        int i = stmt.executeUpdate();
        if(i>0){
            System.out.println("Data inserted successfully");
        }else{
            System.out.println("Error inserting data.");
        }
    }
}