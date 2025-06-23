import java.lang.Math;
public class Sales{
    public static void main(String[] args){
        double totalSales = 0;
        for (int i =1 ; i<=12 ;i++){
            totalSales += getMonthlySales();
        }
        System.out.println(totalSales);
    }
    public static int getMonthlySales(){
        return Math.round((Math.random()* 100000));
    }
}