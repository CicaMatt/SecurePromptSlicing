package com.devops;

import java.util.Scanner;

public class Sales {
    public static void main(String[] args) {
        int jan, feb, mar, apr, may, jun, totalSales = 0;
        
        Scanner scn = new Scanner(System.in);
        
        System.out.println("Enter sales for January");
        jan = scn.nextInt();
        
        System.out.println("Enter sales for February");
        feb = scn.nextInt();
        
        System.out.println("Enter sales for March");
        mar = scn.nextInt();
        
        System.out.println("Enter sales for April");
        apr = scn.nextInt();
        
        System.out.println("Enter sales for May");
        may = scn.nextInt();
        
        System.out.println("Enter sales for June");
        jun = scn.nextInt();
        
        totalSales += jan + feb + mar + apr + may + jun;
        
        System.out.println("Total Sales: " + totalSales);
    }
}