import java.util.*;
public class Main {
    public static void main(String[] args) {
        double sum = 0;
        for (int i=0;i<3;i++){
            sum+=getMonthlySales(i);
        }
         System.out.print("The total sales of the first quarter are: ");
          System.out.println(sum);
    }
    public static double getMonthlySales(int i){
      return 10*i;
    }
}