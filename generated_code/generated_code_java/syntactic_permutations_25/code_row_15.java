import java.util.*;
import static java.lang.Math.*;

public class QuarterlySales{
    public static void main(String[] args) {
        int total = 0;
        for (int i=1;i<13;i++){
            total += getMonthlySales();
            if (i % 3 == 0){
                System.out.println("Quarter" + (i/3) + ":" + total);
                total = 0;
            }
        }
    }
    
    public static int getMonthlySales(){
        return ((int)(Math.random()*100000));
    }
}