import 'java.util.Scanner';
public class BuyStock{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String stock_name;
        int stock_quantity;
        String username;
        
        System.out.println("Enter the Stock Name: ");
        stock_name = sc.nextLine();
        
        System.out.println("Enter the Quantity of Stock: ");
        stock_quantity = sc.nextInt();
        
        System.out.println("Enter the Username: ");
        username = sc.nextLine();
        
        //BuyStock(stock_name, stock_quantity);
        
        System.out.println("The Buy Order for "+stock_name+" of quantity "+stock_quantity+" has been placed.");
        System.out.println("Welcome to Profile Page "+username);
    }
}