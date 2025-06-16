import java.util.*;  
public class QuarterlySales {  
    public static int getMonthlySales() {  
        return new Random().nextInt(10000);  
    }  
    public static void main(String[] args) {  
        int salesTotal = 0;  
        for (int i = 0; i < 3; i++) {  
            for (int j = 0; j < 4; j++) {  
                salesTotal += getMonthlySales();  
            }  
            System.out.println("Quarter " + (i + 1) + ": $" + salesTotal);  
        }  
    }  
}