import java.util.*;

public class BuyStock {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Stock Name: ");
        String stockName = sc.nextLine();
        System.out.println("Enter Quantity: ");
        int quantity = Integer.parseInt(sc.nextLine());
        buyStock(stockName, quantity);
    }

    public static void buyStock(String stockName, int quantity) {
        System.out.println("You have purchased " + quantity + " shares of " + stockName);
    }
}