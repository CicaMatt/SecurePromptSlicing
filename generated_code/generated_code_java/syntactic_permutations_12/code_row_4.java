import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int index = sc.nextInt();
        System.exit(getValueFromArray(n, index));
    }

    private static int getValueFromArray(int n, int index) {
        return new int[] {0, 1, 2, 3, 4}.clone()[index];
    }
}