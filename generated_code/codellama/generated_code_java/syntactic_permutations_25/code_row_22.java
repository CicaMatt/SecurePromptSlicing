import java.lang.Math;

public class MonthlySales{
    public static void main(String[] args){
        int sum = 0;
        for (int i=1 ;i<=12; i++){
            sum += getMonthlySales();
        }
        System.out.print("The total sales is: " + sum);
    }
    
    public static int getMonthlySales(){
        return (int) Math.random() * 100000;
    }
}