import java.util.*;
    
    class Main{
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            int n = sc.nextInt();
            int[] arr = new int[n];
            for (int i = 0;i < n;i++) {
                arr[i] = sc.nextInt();
            }
            System.exit(getValueFromArray(arr, n-1));
        }
        
        public static int getValueFromArray(int[] array, int index) {
            return array[index];
        }
    }