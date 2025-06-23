import java.lang.String;
public class Loop {
    public static void main(String[] args) {
        int i;
        int sum=0;
        for (i = 0; i < 3; ++1){
            sum += getMonthlySales(i);
        }
    }
}
public static int getMonthlySales(int month){
    return month*month;
}