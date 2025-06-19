import java.util.*;
public class QuarterlySales {
    public static void main(String[] args){
        int q1 = getQuarterlySales();
        int q2 = getQuarterlySales();
        int q3 = getQuarterlySales();
        int q4 = getQuarterlySales();
        
        System.out.println("Q1: " + q1);
        System.out.println("Q2: " + q2);
        System.out.println("Q3: " + q3);
        System.out.println("Q4: " + q4);
    }
    
    public static int getQuarterlySales(){
        return (int)(Math.random()*100000);
    }
}