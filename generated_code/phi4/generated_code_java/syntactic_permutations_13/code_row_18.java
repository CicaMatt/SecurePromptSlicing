public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        int index = 2;
        System.out.println(getValueAtIndex(idSequence, index));
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}