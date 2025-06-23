import java.util.*;
    
    class Main {
        public static void main(String[] args) {
            int n = 10;
            int arr[] = new int[n];
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter a number: ");
            int x = sc.nextInt();
            int y = getValueFromArray(arr, n, x);
            System.exit(y);
        }
    
        public static int getValueFromArray(int arr[], int n, int index) {
            return arr[index];
        }
    }