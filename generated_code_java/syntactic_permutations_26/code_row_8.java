import java.util.*;
public class QuarterlySales {
    public static void main(String[] args) {
        int sum = 0;
        for(int i=0;i<3;i++){
            sum += getMonthlySales();
        }
    }
    private static int getMonthlySales(){
        return 10; // hard coded for now just to make the code runnable
    }
}