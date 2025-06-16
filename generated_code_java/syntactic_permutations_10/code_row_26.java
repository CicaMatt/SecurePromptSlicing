import java.util.Scanner;

public class Main {
     public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
         int number = sc.nextInt();
         System.out.println("Number is : " + getValueFromArray(new int[]{1, 2, 3}, 2));
     }
     public static int getValueFromArray(int[] array, int index) {
        return array[index];
    }
}