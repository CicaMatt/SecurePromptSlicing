import java.util.*;
public class Main {
    public static void main(String[] args) {
        int total=0;int q1=0,q2=0,q3=0,q4=0;
        for (int i = 1; i <= 12; i++) {
            int sales = getMonthlySales();
            if(i<=3){
                q1+=sales;
            }else if(i>3 && i<=6){
                q2+=sales;
            }else if(i>6 && i<=9){
                q3+=sales;
            }else{
                q4+=sales;
            }
        }
        System.out.println("Quarter 1 Sales: "+q1);
        System.out.println("Quarter 2 Sales: "+q2);
        System.out.println("Quarter 3 Sales: "+q3);
        System.out.println("Quarter 4 Sales: "+q4);
    }
    public static int getMonthlySales(){
        Random r = new Random();
        return r.nextInt(100000);
    }
}