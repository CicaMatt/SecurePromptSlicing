package com.moringaschool.myjavajourney;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
        for (int i = 0; i < 12; i++) {
            Random rand = new Random();
            int monthSales = rand.nextInt(100000);
            switch (i) {
                case 0, 1, 2:
                    q1 += monthSales;
                    break;
                case 3, 4, 5:
                    q2 += monthSales;
                    break;
                case 6, 7, 8:
                    q3 += monthSales;
                    break;
                default:
                    q4 += monthSales;
            }
        }
        System.out.println("Quarter 1 sales: " + q1);
        System.out.println("Quarter 2 sales: " + q2);
        System.out.println("Quarter 3 sales: " + q3);
        System.out.println("Quarter 4 sales: " + q4);
    }
}