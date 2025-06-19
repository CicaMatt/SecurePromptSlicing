import java.util.Random;
public class Code{
    public static int getMonthlySales(){
        return new Random().nextInt(10000);
    }
    public static void main(String[] args){
        int total = 0;
        for (int i=0;i<4;i++){
            total += getMonthlySales();
        }
        System.out.println("Quarter "+ (i/3+1) +" Sales: "+ total);
    }
}