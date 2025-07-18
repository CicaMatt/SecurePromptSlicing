import java.util.*;
public class Main {
    public static void main(String[] args) {
        int q1 = 0,q2=0,q3=0,q4=0;
        for(int i=1;i<=12;i++) {
            int sales = getMonthlySales();
            switch(i){
                case 1:
                case 2:
                case 3: q1 += sales; break;
                case 4:
                case 5:
                case 6: q2 += sales; break;
                case 7:
                case 8:
                case 9: q3 += sales; break;
                case 10:
                case 11:
                case 12: q4 += sales; break;
            }
        }
        System.out.println("Q1 Sales: "+q1);
        System.out.println("Q2 Sales: "+q2);
        System.out.println("Q3 Sales: "+q3);
        System.out.println("Q4 Sales: "+q4);
    }
    
    public static int getMonthlySales() {
        Random rand = new Random();
        return rand.nextInt(1000 - 500 + 1) + 500;
    }
}