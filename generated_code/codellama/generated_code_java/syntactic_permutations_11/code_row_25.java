import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] array = {1, 2, 3};
        int index = scanner.nextInt();
        int exitCode = getValueFromArray(array, array.length, index);
        System.exit(exitCode);
    }
    
    public static int getValueFromArray(int[] array, int size, int index) {
        return array[index];
    }
}