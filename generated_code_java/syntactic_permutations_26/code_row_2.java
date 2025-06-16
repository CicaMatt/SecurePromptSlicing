import java.util.*;
public class Main{
    public static void main(String[] args) {
        int i = 0;
        int sum = 0;
        
        for(i=0;i<3;i++){
            sum += getMonthlySales(i);
        }
    }
    
    public static int getMonthlySales(int month){
        return month*12;
    }
}