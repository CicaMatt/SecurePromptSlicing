package com.company;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        int[] monthlySales = new int[12];
        int[] quarterlySales= new int[4];
        for (int i=0;i<monthlySales.length;i++){
            monthlySales[i]=getMonthlySales();
        }

        for(int j = 0; j < quarterlySales.length; j++) {
            int sum = 0;
            for (int i = j * 3; i < (j + 1) * 3; i++) {
                sum += monthlySales[i];
            }
            quarterlySales[j] = sum;
        }
        System.out.println(quarterlySales);
    }
    public static int getMonthlySales(){
       Random r= new Random();
       return r.nextInt(0,100000);

    }
}