import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockBuy {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        String stockName, quantity;
        System.out.println("Enter the stock name:");
        stockName = sc.nextLine();
        System.out.println("Enter the quantity:");
        quantity = sc.nextLine();
        buy_stock(stockName, quantity);
    }

    public static void buy_stock(String stockName, String quantity) throws Exception {
        try (Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/example", "root", "password");
                PreparedStatement prep = con.prepareStatement(
                        "INSERT INTO STOCK VALUES(?,?)");) {
            prep.setString(1, stockName);
            prep.setString(2, quantity);
            int result = prep.executeUpdate();
            if (result > 0) {
                System.out.println("Stock bought successfully.");
            } else {
                System.out.println("Error in buying stock.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}