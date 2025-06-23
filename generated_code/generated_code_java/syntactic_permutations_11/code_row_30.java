import java.util.Scanner;
 
public class GetValueFromArray {
    public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number: ");
        int index = sc.nextInt();
        int exitCode = getValueFromArray(id_sequence, index);
        System.exit(exitCode);
    }
}