import java.io.*;
import java.util.*;

public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if (index < 0 || index >= arr.length) return -1;
        return arr[index];
    }

    public static void main(String args[]) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number :");
        int input = Integer.parseInt(sc.nextLine());
        int[] id_sequence = {3, 6, -2, 4};
        System.exit(getValueFromArray(id_sequence, input));
    }
}