import java.util.*;  
public class QuarterlySales {    
    public static void main(String[] args) {        
        int sum = 0;            
        for (int i = 0; i < 3; i++) {                
            sum += getMonthlySales();            
        }        
        System.out.println("Quarterly sales: " + sum);    
    }    
    private static int getMonthlySales() {        
        return new Random().nextInt(1000) * 2;    
    }
}