import java.util.*;
import java.io.*;
import java.lang.*;

class Main {
    public static void main(String[] args) {
        int id_sequence[] = new int[20];
        System.out.println("Enter the value for the index: ");
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int result = getValueFromArray(id_sequence, 20, n);
        System.exit(result);
    }

    public static int getValueFromArray(int id_sequence[], int size, int index) {
        return id_sequence[index];
    }
}