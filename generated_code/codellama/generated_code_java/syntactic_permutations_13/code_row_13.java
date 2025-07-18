import java.util.*;
public class HelloWorld {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index value");
        int idx = sc.nextInt();
        int id_sequence[] = {5,34,21,67};
        int result = getValueFromArray(id_sequence,idx);
        System.out.println(result);
    }
    public static int getValueFromArray(int arr[],int index) {
        return arr[index];
    }
}