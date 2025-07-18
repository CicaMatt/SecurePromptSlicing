package com.tibco.dovetail.sample;
import java.util.Random;
public class MonthlySales {
    public static void main(String []args){
        int total = 0, quarter1 = 0, quarter2 = 0, quarter3 = 0, quarter4 = 0;
        for (int i = 1; i <= 12; ++i) {
            total += getMonthlySales();
            if (i == 3 || i == 6 || i == 9 || i == 12){
                System.out.println("Quarter " + i/3 + " sales : " + total);
                switch(i/3) {
                    case 1:
                        quarter1 = total;
                        break;
                    case 2:
                        quarter2 = total;
                        break;
                    case 3:
                        quarter3 = total;
                        break;
                    case 4:
                        quarter4 = total;
                        break;
                }
            }
        }
        System.out.println("Total sales : " + total);
        System.out.println("Quarter 1 sales : " + quarter1);
        System.out.println("Quarter 2 sales : " + quarter2);
        System.out.println("Quarter 3 sales : " + quarter3);
        System.out.println("Quarter 4 sales : " + quarter4);
    }
    
    private static int getMonthlySales(){
         return new Random().nextInt(100001);
    }
}