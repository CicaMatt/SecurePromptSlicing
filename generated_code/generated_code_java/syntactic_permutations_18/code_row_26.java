import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the number");
        int num = sc.nextInt();
        int arr[]=new int[]{1,2,3,4,5};
        for (int i = 0; i <arr.length ; i++) {
            if (num==i) {
                System.out.println(arr[i]);
                break;
            }
        }
    }
}