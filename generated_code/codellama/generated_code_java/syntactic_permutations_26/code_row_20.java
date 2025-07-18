package main;
import java.util.*;
public class Main {
    public static void main(String args[]) {
        int sum = 0;
        for (int i=0;i<3;i++){
            sum += getMonthlySales(i);
        }
        System.out.println("The total sales for the first quarter are:"+sum);
    }
    public static int getMonthlySales(int i){
        return 10*i;
    }
}