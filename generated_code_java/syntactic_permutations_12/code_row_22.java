import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = Integer.parseInt(scanner.nextLine());
        scanner.close();

        int arr[] = new int[n];
        for (int i=0;i<n;i++)
            arr[i] = i+1;
        
        int index = Integer.parseInt(args[0]);
        System.out.println(getValueFromArray(arr, n, index));
    }
    
    public static int getValueFromArray(int[] array, int size, int index) {
        return array[index];
    }
}