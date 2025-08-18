public class Main {
    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5};
        int size = array.length;
        int index = 2; // Example index

        try {
            int value = getValueFromArray(array, size, index);
            System.exit(value);
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
            System.exit(1); // Exit with code 1 to indicate an error
        }
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            throw new IllegalArgumentException("Index out of bounds");
        }
        return array[index];
    }
}