import java.util.ArrayList;
public class Sales {
    public static void main(String[] args) {
        int sum = 0;
        for (int i=0;i<3;i++){
            sum+=getMonthlySales(i);
        }
        System.out.println("Total sales: " + sum);
    }
    static int getMonthlySales(int month){
        return 10000 + (month+1)*25;
    }
}