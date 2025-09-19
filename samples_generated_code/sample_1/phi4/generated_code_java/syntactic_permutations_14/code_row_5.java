public class IndexValueFetcher {

    public static int getValueAtIndex(int[] idSequence, int index) {
        if (index < 0 || index >= idSequence.length) {
            throw new IllegalArgumentException("Index out of bounds");
        }
        return idSequence[index];
    }

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        int index = 2;
        
        try {
            int value = getValueAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
}