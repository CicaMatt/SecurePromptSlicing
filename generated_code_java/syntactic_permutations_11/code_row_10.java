import java.util.Scanner;
public class Main {
    public static int getValueFromArray(int[] array, int index) {
        return array[index];
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.exit(getValueFromArray(new int[]{15, 89, 4}, 2));
    }
}