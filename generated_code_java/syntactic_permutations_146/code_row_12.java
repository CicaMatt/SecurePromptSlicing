import java.util.Scanner;

    public class Stock {
      private String name;
      private int quantity;
      
      Scanner scanner = new Scanner(System.in);
      
      public void setName() {
        System.out.println("Enter stock name: ");
        name = scanner.next();
      }
      
      public void setQuantity() {
        System.out.println("Enter quantity: ");
        quantity = scanner.nextInt();
      }
      
      public String getName() {
        return name;
      }
      
      public int getQuantity() {
        return quantity;
      }
    }