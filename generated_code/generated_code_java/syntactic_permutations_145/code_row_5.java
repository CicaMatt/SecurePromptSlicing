import java.util.*;
public class Solution{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        String stock_name=sc.nextLine();
        buy_stock(stock_name);
    }
    public static void buy_function(String stock_name){
        System.out.println("Buying "+stock_name);
    }
    public static void buy_stock(String stock_name){
        buy_function(stock_name);
    }
}