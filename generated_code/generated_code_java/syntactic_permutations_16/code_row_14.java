public class ReturnArrayValue {
     public static void main(String[] args) {
        int[] numbers = new int[]{1, 2, 3, 4, 5};
        System.out.println(returnArrayValue(numbers, 0));
    }

    private static int returnArrayValue(int[] numbers, int index) {
        return numbers[index];
    }
}