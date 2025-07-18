import java.util.*;
public class Solution{
    public static void main(String[] args){
        int[] months = {1,2,3,4,5,6,7,8,9,10,11,12};
        for (int month : months) {
            System.out.println("Month " + month + ":");
            System.out.println(getMonthlySales());
        }
    }
    
    public static int getMonthlySales(){
        return new Random().nextInt(100000);
    }
}