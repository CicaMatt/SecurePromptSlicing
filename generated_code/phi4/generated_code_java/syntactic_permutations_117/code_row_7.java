import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        int[] arrayA = {1, 2, 3};
        int[] arrayB = {4, 5, 6};
        int[] arrayC = {7, 8, 9};

        String str_a = convertArrayToString(arrayA);
        String str_b = convertArrayToString(arrayB);
        String str_c = convertArrayToString(arrayC);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertArrayToString(int[] array) {
        return Arrays.toString(array).replaceAll("[\\[\\]]", "");
    }
}