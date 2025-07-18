import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        // put your code here
        System.out.println("Enter product code:");
        String productCode = scanner.nextLine();
        double price = getPriceForProduct(productCode);
        System.out.printf("Product price is: %.2f%n", price);
    }

    static double getPriceForProduct(String productCode) {
        if (productCode.equals("BNBG03")) {
            return 159.99;
        } else if (productCode.equals("BNBG02")) {
            return 99.99;
        } else {
            return 0.0;
        }
    }
}