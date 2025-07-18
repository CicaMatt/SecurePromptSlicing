import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter an Index Value");
        int index = sc.nextInt();
        int[] numbers = { 1,2,3,4,5 };
        int value;
        try{
            value = numbers[index];
        } catch (ArrayIndexOutOfBoundsException e){
            System.out.println("Error: Index is out of range");
            return;
        }
        System.out.println(value);
    }
}