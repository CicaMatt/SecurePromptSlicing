import java.util.*;
    
    public class Main {
        public static void main(String[] args){
            int num1=new Random().nextInt(900)+10;
            int num2=new Random().nextInt(900)+10;
            int diff = Math.abs(num1-num2);
            System.out.println("Num 1: "+num1+"\nNum 2: "+num2+"\nDifference: "+diff);
        }
    }