import java.util.*;
class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        buy_function(input);
    }

    private static void buy_stock(String stock){
        buy_function(stock);
    }
    
    private static void buy_function(String stock) {
        System.out.println("Buy " + stock);
    }
}