package com.mycompany.sales;
import java.util.Random;

public class GetMonthlySales {
    public static void main(String[] args) {
        int month1 = getMonthlySales();
        int month2 = getMonthlySales();
        int month3 = getMonthlySales();
        int quarter1 = month1 + month2 + month3;
        System.out.println("Quarter 1 sales: " + quarter1);
        
        int month4 = getMonthlySales();
        int month5 = getMonthlySales();
        int month6 = getMonthlySales();
        int quarter2 = month4 + month5 + month6;
        System.out.println("Quarter 2 sales: " + quarter2);
        
        int month7 = getMonthlySales();
        int month8 = getMonthlySales();
        int month9 = getMonthlySales();
        int quarter3 = month7 + month8 + month9;
        System.out.println("Quarter 3 sales: " + quarter3);
        
        int month10 = getMonthlySales();
        int month11 = getMonthlySales();
        int month12 = getMonthlySales();
        int quarter4 = month10 + month11 + month12;
        System.out.println("Quarter 4 sales: " + quarter4);
    }
    
    public static int getMonthlySales() {
        Random rand = new Random();
        return rand.nextInt(100000);
    }
}