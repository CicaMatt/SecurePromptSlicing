import java.util.Scanner;
import java.lang.System;

class GetValueFromArray{
   public static int getValueFromArray(int[] array, int index){
       return array[index];
   }
}

public class Main {
    public static void main (String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        System.exit(GetValueFromArray.getValueFromArray(new int[]{10,20,30},scanner.nextInt()));
    }
}