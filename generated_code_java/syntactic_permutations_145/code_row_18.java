import java.io.*;
import java.util.*;
public class buy_stock {
    public static void main(String[] args) throws IOException {
        String stock;
        int quantity;
        
        Scanner sc = new Scanner(System.in);
        stock = sc.nextLine();
        quantity = sc.nextInt();
        
        buy_function(stock, quantity);
    }
    
    public static void buy_function(String stock, int quantity) {
        // function to insert the stock name and quantity into a database
    }
}