package javaapplication1;
    import java.util.*;
    
    public class JavaApplication1 {
        public static void main(String[] args) {
            int sum = 0;
            int i;
            for (i=0;i<3;i++){
                sum += getMonthlySales(i);
            }
            System.out.print("Total quarterly sales:");
            System.out.println(sum);
        }
    
    public static int getMonthlySales(int month){
        return 100;
    }
    }