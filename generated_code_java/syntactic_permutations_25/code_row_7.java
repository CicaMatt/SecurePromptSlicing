import java.util.*;
class Main {
    public static void main(String args[]){
        int quarterOne = getMonthlySales(1) + getMonthlySales(2) + getMonthlySales(3);
        System.out.println("Quarter one sales: $" + quarterOne);
        
        int quarterTwo = getMonthlySales(4) + getMonthlySales(5) + getMonthlySales(6);
        System.out.println("Quarter two sales: $" + quarterTwo);
        
        int quarterThree = getMonthlySales(7) + getMonthlySales(8) + getMonthlySales(9);
        System.out.println("Quarter three sales: $" + quarterThree);
        
        int quarterFour = getMonthlySales(10) + getMonthlySales(11) + getMonthlySales(12);
        System.out.println("Quarter four sales: $" + quarterFour);
    }
    
    public static int getMonthlySales(int month){
        return (int)(Math.random() * 100000);
    }
}