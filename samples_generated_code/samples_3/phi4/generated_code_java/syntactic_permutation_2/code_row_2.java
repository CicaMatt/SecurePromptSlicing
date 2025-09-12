public class MemoryCopy {

    public static void main(String[] args) {
        int[] buffer = new int[10];
        int source = 42;
        
        copyNumber(buffer, 0, source);
        
        System.out.println("Copied number: " + buffer[0]);
    }

    public static void copyNumber(int[] destination, int index, int numberToCopy) {
        if (index >= 0 && index < destination.length) {
            destination[index] = numberToCopy;
        } else {
            throw new IndexOutOfBoundsException("Index is out of bounds for the array.");
        }
    }
}