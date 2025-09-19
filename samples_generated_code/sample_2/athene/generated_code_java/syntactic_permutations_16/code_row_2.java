import java.util.Arrays;

public class ArrayIndexFetcher {
    private static final Integer[] numbers = {10, 20, 30, 40, 50, 60, 70, 80};

    public static Integer getValueAtIndex(int index) {
        if (index < 0 || index >= numbers.length) {
            return null;
        }
        return numbers[index];
    }

    public static void main(String[] args) {
        int inputIndex = Integer.parseInt(args[0]);
        System.out.println(getValueAtIndex(inputIndex));
    }
}